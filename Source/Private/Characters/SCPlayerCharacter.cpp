// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SCPlayerCharacter.h"
#include "Player/SCPlayerState.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "AbilitySystem/SCAbilitySystemComponent.h"
#include "DataAssets/DataAsset_InputConfig.h"
#include "EnhancedInputSubsystems.h"
#include "SCGameplayTags.h"
#include "Input/SCEnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DataAssets/CharacterCustomize.h"
#include "Components/Combat/PlayerCombatComponent.h"
#include "Components/Inventory/InventoryComponent.h"
#include "Components/QuickSlot/QuickSlotComponent.h"
#include "AbilitySystem/SCAbilitySystemLibrary.h"
#include "Components/BuildingComponent.h"
#include "Player/SCPlayerController.h"
#include "UI/HUD/SCHUD.h"
#include "SCDebugHelper.h"

ASCPlayerCharacter::ASCPlayerCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 200.f;
	CameraBoom->SocketOffset = FVector(0.f, 55.f, 65.f);
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;


	PlayerCombatComponent = CreateDefaultSubobject<UPlayerCombatComponent>(TEXT("PlayerCombatComponent"));
	
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("PlayerInventoryComponent"));
	InventoryComponent->NumOfSlots = 40;

	QuickSlotComponent = CreateDefaultSubobject<UQuickSlotComponent>(TEXT("PlayerQuickSlotComponent"));
	QuickSlotComponent->NumOfSlots = 8;

	BuildingComponent = CreateDefaultSubobject<UBuildingComponent>(TEXT("BuildingComponent"));
	
}

UPawnCombatComponentBase* ASCPlayerCharacter::GetPawnCombatComponent() const
{
	return PlayerCombatComponent;
}

UInventoryComponent* ASCPlayerCharacter::GetInventoryComponent() const
{
	return InventoryComponent;
}

UQuickSlotComponent* ASCPlayerCharacter::GetQuickSlotComponent() const
{
	return QuickSlotComponent;
}

UBuildingComponent* ASCPlayerCharacter::GetBuildingComponent() const
{
	return BuildingComponent;
}

void ASCPlayerCharacter::GetCameraLocation(FVector& Location)
{
	Location = FollowCamera->GetComponentLocation();
}

void ASCPlayerCharacter::GetCameraForwardVector(FVector& ForwardVector)
{
	ForwardVector = FollowCamera->GetForwardVector();
}

void ASCPlayerCharacter::GetCameraRotation(FRotator& Rotation)
{
	Rotation = FollowCamera->GetComponentRotation();
}

void ASCPlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	InitAbilityActorInfo();
	AddCharacterEffects();
}

void ASCPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (HasAuthority())
	{
		InventoryComponent->GenerateDefaultSlots();
		QuickSlotComponent->GenerateDefaultSlots();
	}


}

void ASCPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitAbilityActorInfo();
	AddCharacterEffects();
	AddCharacterAbilities();
	PlayerCombatComponent->UpdateEquippedArmors();

}

void ASCPlayerCharacter::SetLeaderMesh()
{

	TArray<USceneComponent*> ChildClasses;
	GetMesh()->GetChildrenComponents(true, ChildClasses);
	for (USceneComponent* ChildClass : ChildClasses)
	{
		if (USkeletalMeshComponent* SubMesh = Cast<USkeletalMeshComponent>(ChildClass))
		{
			SubMesh->SetLeaderPoseComponent(GetMesh(),true,true);
		}
	}
}


void ASCPlayerCharacter::InitAbilityActorInfo()
{
	ASCPlayerState* SCPlayerState = GetPlayerState<ASCPlayerState>();
	check(SCPlayerState);
	SCPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(SCPlayerState, this);
	Cast<USCAbilitySystemComponent>(SCPlayerState->GetAbilitySystemComponent())->AbilityActorInfoSet();

	AbilitySystemComponent = SCPlayerState->GetAbilitySystemComponent();
	AttributeSet = SCPlayerState->GetAttributeSet();

	if (ASCPlayerController* SCPlayerController = Cast<ASCPlayerController>(GetController()))
	{
		if (ASCHUD* SCHUD = Cast<ASCHUD>(SCPlayerController->GetHUD()))
		{
			SCHUD->InitWidgets(SCPlayerController, SCPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}
}
