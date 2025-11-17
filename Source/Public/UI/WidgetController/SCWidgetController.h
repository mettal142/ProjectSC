// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AbilitySystemComponent.h"
#include "SCWidgetController.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;
class USCAbilitySystemComponent;
class USCAttributeSet;
class ASCPlayerController;
class ASCPlayerState;
class USCUserWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInitSlotsSignature, int, NumOfSlots);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAddSlotSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnResetSlotSignature, int, SlotIndex);

USTRUCT(BlueprintType)
struct FWidgetControllerParams
{
	GENERATED_BODY()
	FWidgetControllerParams() {}
	FWidgetControllerParams(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
		: PlayerController(PC), PlayerState(PS), AbilitySystemComponent(ASC), AttributeSet(AS) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerController> PlayerController = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerState> PlayerState = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAttributeSet> AttributeSet = nullptr;

};

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class PROJECTSC_API USCWidgetController : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	virtual void SetWidgetControllerParams(const FWidgetControllerParams& WCParams);

	UFUNCTION(BlueprintCallable)
	virtual void BroadcastInitialValues();
	virtual void BindCallbacksToDependencies();

	UFUNCTION(BlueprintCallable)
	virtual void UpdateWidget();



protected:
	ASCPlayerController* GetSCPlayerController();
	ASCPlayerState* GetSCPlayerState();

	USCAbilitySystemComponent* GetSCAbilitySystemComponent();
	USCAttributeSet* GetSCAttributeSet();

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<APlayerController> PlayerController;
	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<APlayerState> PlayerState;
	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<UAttributeSet> AttributeSet;


};
