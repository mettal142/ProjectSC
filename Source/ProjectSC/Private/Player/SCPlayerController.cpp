// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SCPlayerController.h"
#include "Input/SCEnhancedInputComponent.h"
#include "AbilitySystem/SCAbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "UI/HUD/SCHUD.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "SCGameplayTags.h"

void ASCPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InputConfigDataAsset->DefaultInputMappingContext, 0);
		Subsystem->AddMappingContext(InputConfigDataAsset->UIInputMappingContext, 0);
	}
}

void ASCPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	check(InputConfigDataAsset);

	USCEnhancedInputComponent* SCInputComponent = CastChecked<USCEnhancedInputComponent>(InputComponent);

	SCInputComponent->BindNativeInputAction(InputConfigDataAsset, FSCGameplayTags::Get().InputTag_Move, ETriggerEvent::Triggered, this, &ThisClass::Input_Move);
	SCInputComponent->BindNativeInputAction(InputConfigDataAsset, FSCGameplayTags::Get().InputTag_Look, ETriggerEvent::Triggered, this, &ThisClass::Input_Look);

	//UI
	SCInputComponent->BindNativeInputAction(InputConfigDataAsset, FSCGameplayTags::Get().InputTag_UI_Inventory, ETriggerEvent::Completed, this, &ThisClass::Input_ToggleInventory);
	SCInputComponent->BindNativeInputAction(InputConfigDataAsset, FSCGameplayTags::Get().InputTag_UI_Crafting, ETriggerEvent::Completed, this, &ThisClass::Input_ToggleCraftingPanel);

	SCInputComponent->BindAbilityActions(InputConfigDataAsset, this, &ThisClass::Input_AbilityInputPressed, &ThisClass::Input_AbilityInputReleased);
	
	//QuickSlot
	TArray<FGameplayTag> QuickSlotTags = {
	FSCGameplayTags::Get().InputTag_QuickSlot_1,
	FSCGameplayTags::Get().InputTag_QuickSlot_2,
	FSCGameplayTags::Get().InputTag_QuickSlot_3,
	FSCGameplayTags::Get().InputTag_QuickSlot_4,
	FSCGameplayTags::Get().InputTag_QuickSlot_5,
	FSCGameplayTags::Get().InputTag_QuickSlot_6,
	FSCGameplayTags::Get().InputTag_QuickSlot_7,
	FSCGameplayTags::Get().InputTag_QuickSlot_8,
	FSCGameplayTags::Get().InputTag_QuickSlot_9,
	FSCGameplayTags::Get().InputTag_QuickSlot_0
	};

	for (int i = 0; i < QuickSlotTags.Num(); i++)
	{
		FGameplayTag Tag = QuickSlotTags[i];

		if (UInputAction* FoundAction = InputConfigDataAsset->FindNativeInputActionByTag(Tag))
		{
			SCInputComponent->BindAction(FoundAction, ETriggerEvent::Started, this, &ThisClass::QuickSlotTriggered, i);
		}
	}

}

void ASCPlayerController::SwitchInputMode(EGameState GameState)
{
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (!Subsystem) return;

	switch (GameState)
	{
	case EGameState::Playing:
		Subsystem->AddMappingContext(InputConfigDataAsset->DefaultInputMappingContext, 0);
		break;

	case EGameState::InGameMenu:
		Subsystem->RemoveMappingContext(InputConfigDataAsset->DefaultInputMappingContext);
		break;	
	}
}



USCAbilitySystemComponent* ASCPlayerController::GetASC()
{
	if (!SCAbilitySystemComponent)
	{
		SCAbilitySystemComponent = Cast<USCAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}

	return SCAbilitySystemComponent;
}

void ASCPlayerController::Input_Move(const FInputActionValue& InputActionValue)
{
	if(APawn* ControlledPawn = GetPawn<APawn>())
	{
		const FVector2D MovementVector = InputActionValue.Get<FVector2D>();
		const FRotator MovementRotation(0.f, GetControlRotation().Yaw, 0.f);

		if (MovementVector.Y != 0.f)
		{
			const FVector ForwardDirection = MovementRotation.RotateVector(FVector::ForwardVector);
			ControlledPawn->AddMovementInput(ForwardDirection, MovementVector.Y);

		}
		if (MovementVector.X != 0.f)
		{
			const FVector RightDirection = MovementRotation.RotateVector(FVector::RightVector);

			ControlledPawn->AddMovementInput(RightDirection, MovementVector.X);
		}
	}
}

void ASCPlayerController::Input_Look(const FInputActionValue& InputActionValue)
{
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();

		if (LookAxisVector.X != 0.f)
		{
			ControlledPawn->AddControllerYawInput(LookAxisVector.X);
		}
		if (LookAxisVector.Y != 0.f)
		{
			ControlledPawn->AddControllerPitchInput(LookAxisVector.Y);
		}
	}

}

void ASCPlayerController::Input_ToggleInventory(const FInputActionValue& InputActionValue)
{
	Cast<ASCHUD>(GetHUD())->ToggleInGameMenu(EMenuType::Inventory);
}

void ASCPlayerController::Input_ToggleCraftingPanel(const FInputActionValue& InputActionValue)
{
	Cast<ASCHUD>(GetHUD())->ToggleInGameMenu(EMenuType::Crafting);
}



void ASCPlayerController::QuickSlotTriggered(int SlotIndex)
{
	ActiveQuickSlotActionSignature.ExecuteIfBound(SlotIndex);
}

void ASCPlayerController::Input_AbilityInputPressed(FGameplayTag InInputTag)
{
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		GetASC()->AbilityInputTagPressed(InInputTag);

	}
	//FString Log = FString::Printf(TEXT("Character Name : %s Pressed Tag : %s"),*GetActorNameOrLabel(), *InInputTag.ToString());
	//Debug::Print(Log);
}

void ASCPlayerController::Input_AbilityInputReleased(FGameplayTag InInputTag)
{
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		GetASC()->AbilityInputTagReleased(InInputTag);
	}
	//FString Log = FString::Printf(TEXT("Character Name : %s Released Tag : %s"), *GetActorNameOrLabel(), *InInputTag.ToString());
	//Debug::Print(Log);

}

void ASCPlayerController::Input_AbilityInputHeld(FGameplayTag InInputTag)
{
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{

	}
	//FString Log = FString::Printf(TEXT("Character Name : %s Pressed Tag : %s"), *GetActorNameOrLabel(), *InInputTag.ToString());
	//Debug::Print(Log);
}
