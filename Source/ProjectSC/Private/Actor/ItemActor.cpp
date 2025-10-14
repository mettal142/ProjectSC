// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/ItemActor.h"
#include "Characters/SCPlayerCharacter.h"
#include "Components/Inventory/InventoryComponent.h"
#include "Net/UnrealNetwork.h"
#include "Components/SphereComponent.h"

AItemActor::AItemActor()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	SetRootComponent(ItemMesh);
	ItemMesh->SetIsReplicated(true);
	ItemMesh->SetSimulatePhysics(true);

	PickupRange = CreateDefaultSubobject<USphereComponent>(TEXT("PickupRange"));
	PickupRange->SetupAttachment(GetRootComponent());
	PickupRange->InitSphereRadius(200.f);
	PickupRange->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	PickupRange->SetIsReplicated(true);
	
}

void AItemActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AItemActor, ItemInfo);
}

void AItemActor::BeginPlay()
{
	Super::BeginPlay();

	PickupRange->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnBeginOverlap);
	
}

void AItemActor::ServerPickupItem_Implementation(ASCPlayerCharacter* PlayerCharacter)
{
	if (!bPickUp)
	{
		if (!PlayerCharacter->GetInventoryComponent()) return;
		PlayerCharacter->GetInventoryComponent()->ServerAddItem(ItemInfo);
		bPickUp = true;
		Destroy();


	}
	else
	{
		Destroy();

	}
}


void AItemActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemActor::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ASCPlayerCharacter* Player = Cast<ASCPlayerCharacter>(Other))
	{
		ServerPickupItem(Player);		
	}

}

void AItemActor::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void AItemActor::SetItemInfo(const FSCItemStructure& InItemInfo)
{
	ItemInfo = InItemInfo; 
}

