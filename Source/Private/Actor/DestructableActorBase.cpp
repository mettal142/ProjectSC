// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/DestructableActorBase.h"
#include "Components/BoxComponent.h"
#include "GeometryCollection/GeometryCollectionComponent.h"
#include "Characters/SCPlayerCharacter.h"
#include "Components/Inventory/InventoryComponent.h"
#include "SCGameInstance.h"
#include "SCDebugHelper.h"
#include "SCTypes/SCStructTypes.h"
#include "Net/UnrealNetwork.h"
#include "AbilitySystem/SCAbilitySystemComponent.h"
#include "AbilitySystem/SCAttributeSet.h"
#include "Actor/ItemActor.h"
#include "Kismet/KismetMathLibrary.h"
#include "Field/FieldSystemActor.h"
#include "SCGameplayTags.h"

ADestructableActorBase::ADestructableActorBase()
{ 	
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	ActorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ActorMesh"));
	ActorMesh->SetupAttachment(GetRootComponent());

	DestMesh = CreateDefaultSubobject<UGeometryCollectionComponent>(TEXT("DestMesh"));
	DestMesh->SetupAttachment(ActorMesh);
	DestMesh->SetIsReplicated(true);
	DestMesh->SetVisibility(false);

	FCollisionResponseContainer ResponseContainer;
	ResponseContainer.SetResponse(ECC_Pawn, ECR_Ignore);
	ResponseContainer.SetResponse(ECC_Camera, ECR_Ignore);
	ResponseContainer.SetResponse(ECC_Visibility, ECR_Ignore);

	//DestMesh->SetCollisionResponseToChannels(ResponseContainer);

	DestMesh->SetSimulatePhysics(false);

	BoxOverlap = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxOverlap"));
	BoxOverlap->SetupAttachment(ActorMesh);

	ASC = CreateDefaultSubobject<USCAbilitySystemComponent>(TEXT("SCAbilitySystemComponent"));
	SCAttributeSet = CreateDefaultSubobject<USCAttributeSet>(TEXT("SCAttributeSet"));

}


void ADestructableActorBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ADestructableActorBase, DropItems);

}


UAbilitySystemComponent* ADestructableActorBase::GetAbilitySystemComponent() const
{
	return ASC;
}

void ADestructableActorBase::OnHit(AActor* CausedActor)
{
	//ServerCreateDropItem();
	if (bIsDead) return;
	Debug::Print(TEXT("Hit"));

	if (HasAuthority())
	{
		if (ASCPlayerCharacter* Player = Cast<ASCPlayerCharacter>(CausedActor))
		{
			for (FDropItemStructure& DropItem : DropItems)
			{
				if (DropItem.Amount > 0 && UKismetMathLibrary::RandomBoolWithWeight(DropItem.DropChance))
				{
					FSCItemStructure NewItemInfo;
					if (GI->DataManager->GetItemByID(DropItem.DropItemID, NewItemInfo))
					{
						DropItem.Amount--;
						Player->GetInventoryComponent()->ServerAddItem(NewItemInfo);
					}
				}
			}
		}
	}
	ASC->ExecuteGameplayCue(HitSoundCueTag);


}

void ADestructableActorBase::Die(AActor* CausedActor)
{
	if (bIsDead) return;
	Debug::Print(TEXT("Dead"));
	//ServerCreateAllDropItem();
	if (HasAuthority())
	{
		if (ASCPlayerCharacter* Player = Cast<ASCPlayerCharacter>(CausedActor))
		{
			for (FDropItemStructure& DropItem : DropItems)
			{

				FSCItemStructure NewItemInfo;
				if (DropItem.Amount > 0 && GI->DataManager->GetItemByID(DropItem.DropItemID, NewItemInfo))
				{

					if (NewItemInfo.bIsStackable)
					{						
						NewItemInfo.ItemQuantity = DropItem.Amount;
						Player->GetInventoryComponent()->ServerAddItem(NewItemInfo);
					}
					else
					{
						for (int i = 0; i < DropItem.Amount; i++)
						{
							Player->GetInventoryComponent()->ServerAddItem(NewItemInfo);
						}
					}
					DropItem.Amount = 0;

				}
			}
		}
	}
	bIsDead = true;
	MulticastDestruction();


}

void ADestructableActorBase::ExecuteHitEffect_Implementation(const FVector& HitLocation)
{
	FGameplayCueParameters Params;
	Params.Location = HitLocation;
	ASC->ExecuteGameplayCue(HitEffectCueTag, Params);
}



void ADestructableActorBase::MulticastDestruction_Implementation()
{
	ActorMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);	
	ActorMesh->SetVisibility(false);

	DestMesh->SetVisibility(true);
	DestMesh->SetSimulatePhysics(true);

	FTransform SpawnTransfrom;
	SpawnTransfrom.SetLocation(GetActorLocation());

	GetWorld()->SpawnActor<AFieldSystemActor>(DestForceActorClass, SpawnTransfrom);
	SetLifeSpan(3);

}

void ADestructableActorBase::ServerCreateAllDropItem_Implementation()
{
	check(GI);

	for (FDropItemStructure& DropItem : DropItems)
	{
		if (DropItem.Amount > 0)
		{
			
			FSCItemStructure NewItemInfo;
			if (GI->DataManager->GetItemByID(DropItem.DropItemID, NewItemInfo))
			{
				if (UStaticMesh* ItemMesh = DropItem.DropItemMesh.LoadSynchronous())
				{
					if (NewItemInfo.bIsStackable)
					{
						if (AItemActor* SpawndActor = GetWorld()->SpawnActor<AItemActor>(AItemActor::StaticClass(), FTransform()))
						{
							NewItemInfo.ItemQuantity = DropItem.Amount;
							SpawndActor->ItemMesh->SetStaticMesh(ItemMesh);
							SpawndActor->SetItemInfo(NewItemInfo);
						}
					}
					else
					{
						for (int i = 0; i < DropItem.Amount; i++)
						{
							if (AItemActor* SpawndActor = GetWorld()->SpawnActor<AItemActor>(AItemActor::StaticClass(), FTransform()))
							{								
								SpawndActor->ItemMesh->SetStaticMesh(ItemMesh);
								SpawndActor->SetItemInfo(NewItemInfo);
							}
						}
					}

				}

			}
		}

	}
}


void ADestructableActorBase::ServerCreateDropItem_Implementation()
{
	check(GI);

	for (FDropItemStructure& DropItem : DropItems)
	{
		if (DropItem.Amount > 0)
		{
			if (UKismetMathLibrary::RandomBoolWithWeight(DropItem.DropChance))
			{
				FSCItemStructure NewItemInfo;
				if (GI->DataManager->GetItemByID(DropItem.DropItemID, NewItemInfo))
				{
					if (UStaticMesh* ItemMesh = DropItem.DropItemMesh.LoadSynchronous())
					{
						DropItem.Amount--;
						if (AItemActor* SpawndActor = GetWorld()->SpawnActor<AItemActor>(AItemActor::StaticClass(), FTransform()))
						{
							SpawndActor->ItemMesh->SetStaticMesh(ItemMesh);
							SpawndActor->SetItemInfo(NewItemInfo);

						}

					}

				}
			}
		}

	}
}




void ADestructableActorBase::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		GI = CastChecked<USCGameInstance>(GetWorld()->GetGameInstance());
		check(GI);
		FDropTableStructure DropTableStructure;
		GI->DataManager->GetDropItemByID(DropTableID, DropTableStructure);
		for (const FDropItemStructure& DropItemFromTable: DropTableStructure.DropItems)
		{
			if (UKismetMathLibrary::RandomBoolWithWeight(DropItemFromTable.HeldItemChance))
			{
				FDropItemStructure DropItem;
				DropItem.DropChance = DropItemFromTable.DropChance;
				DropItem.DropItemID = DropItemFromTable.DropItemID;
				DropItem.DropItemMesh = DropItemFromTable.DropItemMesh;				

				DropItem.Amount = FMath::RandRange(DropItemFromTable.MinAmount, DropItemFromTable.MaxAmount);
				DropItems.Add(DropItem);
			}
		}

		if (ASC)
		{
			ASC->InitAbilityActorInfo(this, this);
		}

		for (const TSubclassOf<UGameplayEffect>& EffectClass : Effects)
		{
			if (!EffectClass) continue;

			UGameplayEffect* EffectCDO = EffectClass->GetDefaultObject<UGameplayEffect>();

			ASC->ApplyGameplayEffectToSelf(
				EffectCDO,
				1,
				ASC->MakeEffectContext()
			);

		}
	}
}
