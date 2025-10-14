// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SCCharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "AbilitySystem/Data/PlayerStartupData.h"
#include "AbilitySystem/SCAbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MotionWarpingComponent.h"
#include "DataAssets/CharacterCustomize.h"
#include "SCDebugHelper.h"

// Sets default values
ASCCharacterBase::ASCCharacterBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetCapsuleComponent()->SetGenerateOverlapEvents(false);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetGenerateOverlapEvents(true);

	MotionWarpingComponent = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarpingComponent"));
	MotionWarpingComponent->SetIsReplicated(true);

}

UPawnCombatComponentBase* ASCCharacterBase::GetPawnCombatComponent() const
{
	return nullptr;
}

bool ASCCharacterBase::IsDead_Implementation() const
{
	return bIsDead;
}

AActor* ASCCharacterBase::GetAvatar_Implementation()
{
	return this;
}

UAnimMontage* ASCCharacterBase::GetHitReactMontage_Implementation()
{
	return HitReactMontage;
}

void ASCCharacterBase::AcceptClientMovement(bool Value)
{
	GetCharacterMovement()->bIgnoreClientMovementErrorChecksAndCorrection = Value;
	GetCharacterMovement()->bServerAcceptClientAuthoritativePosition = Value;

}

UAbilitySystemComponent* ASCCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ASCCharacterBase::OnHit(AActor* CausedActor)
{
}

UAnimMontage* ASCCharacterBase::GetDeadMontage_Implementation()
{
	return DeadMontage;
}

void ASCCharacterBase::Die(AActor* CausedActor)
{
	MulticastHandleDeath_Implementation();
}

USkeletalMeshComponent* ASCCharacterBase::GetMeshByTag(FGameplayTag EquippedSocket)
{
	if (CharacterMeshMap.Contains(EquippedSocket))
	{
		return CharacterMeshMap[EquippedSocket];
	}

	return nullptr;
}

void ASCCharacterBase::MulticastHandleDeath_Implementation()
{
	// GetMesh()->SetSimulatePhysics(true);
	// GetMesh()->SetEnableGravity(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	GetMesh()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);

	if (DeadMontage)
	{
		PlayAnimMontage(DeadMontage);

	}


	bIsDead = true;

}

void ASCCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

}

void ASCCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	InitializeMeshes();
}

void ASCCharacterBase::InitAbilityActorInfo()
{
}

void ASCCharacterBase::AddCharacterEffects()
{
	USCAbilitySystemComponent* ASC = CastChecked<USCAbilitySystemComponent>(AbilitySystemComponent);

	if (!CharacterStartupData.IsNull())
	{
		if (UStartupDataBase* LoadedData = CharacterStartupData.LoadSynchronous())
		{
			LoadedData->ApplyEffectToCharacter(this, ASC);
		}
	}
}

void ASCCharacterBase::AddCharacterAbilities()
{
	USCAbilitySystemComponent* ASC = CastChecked<USCAbilitySystemComponent>(AbilitySystemComponent);
	if (!HasAuthority()) return;
	if (!CharacterStartupData.IsNull())
	{
		if (UStartupDataBase* LoadedData = CharacterStartupData.LoadSynchronous())
		{
			LoadedData->GiveToAbilitySystemComponent(ASC);
		}
	}
}

void ASCCharacterBase::InitializeMeshes()
{
	if (!CharacterCustomize) return;


	for (const FCustomizableMesh& CustomizableMesh : CharacterCustomize->CharacterMeshList)
	{

		if (CustomizableMesh.Tag.MatchesTagExact(FSCGameplayTags::Get().EquippableSocket_Head))
		{
			GetMesh()->SetSkeletalMesh(CustomizableMesh.Mesh);

			GetMesh()->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform);
			for (int j = 0; j < CustomizableMesh.Materials.Num(); j++)
			{
				GetMesh()->SetMaterial(j, CustomizableMesh.Materials[j]);
			}
			CharacterMeshMap.Add(CustomizableMesh.Tag, GetMesh());

		}
		else
		{
			USkeletalMeshComponent* NewMesh = NewObject<USkeletalMeshComponent>(this);
			NewMesh->RegisterComponent();
			NewMesh->SetSkeletalMesh(CustomizableMesh.Mesh);
			NewMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform);
			for (int j = 0; j < CustomizableMesh.Materials.Num(); j++)
			{
				NewMesh->SetMaterial(j, CustomizableMesh.Materials[j]);
			}
			CharacterMeshMap.Add(CustomizableMesh.Tag, NewMesh);
			NewMesh->SetLeaderPoseComponent(GetMesh());
		}
	}

	for (const FName& SlotName : GetMesh()->GetMaterialSlotNames())
	{
		if (CharacterCustomize->MaterialMap.Contains(SlotName))
		{
			GetMesh()->SetMaterialByName(SlotName, CharacterCustomize->MaterialMap.FindRef(SlotName));
		}
	}
}
