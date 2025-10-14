// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"
#include "SCTypes/SCEnumTypes.h"
#include "SCPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class UDataAsset_InputConfig;
class USCAbilitySystemComponent;

struct FInputActionValue;
DECLARE_DELEGATE_OneParam(FActiveQuickSlotActionSignature, int);


/**
 * 
 */
UCLASS()
class PROJECTSC_API ASCPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	void SwitchInputMode(EGameState GameState);
	USCAbilitySystemComponent* GetASC();	

	FActiveQuickSlotActionSignature ActiveQuickSlotActionSignature;
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;


#pragma region Input
	void Input_Move(const FInputActionValue& InputActionValue);
	void Input_Look(const FInputActionValue& InputActionValue);
	void Input_ToggleInventory(const FInputActionValue& InputActionValue);
	void Input_ToggleCraftingPanel(const FInputActionValue& InputActionValue);

	
	void QuickSlotTriggered(int SlotIndex);

	void Input_AbilityInputPressed(FGameplayTag InInputTag);
	void Input_AbilityInputReleased(FGameplayTag InInputTag);
	void Input_AbilityInputHeld(FGameplayTag InInputTag);



	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterData", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UDataAsset_InputConfig> InputConfigDataAsset;
#pragma endregion

	UPROPERTY()
	TObjectPtr<USCAbilitySystemComponent> SCAbilitySystemComponent;

};
