// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/SCWidgetController.h"
#include "QuickSlotWidgetController.generated.h"

struct FQuickSlotStructure;
class UQuickSlotComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpdateAllQuickSlotsSignature, const TArray<FQuickSlotStructure>&, Slots);


/**
 * 
 */
UCLASS()
class PROJECTSC_API UQuickSlotWidgetController : public USCWidgetController
{
	GENERATED_BODY()

public:
	virtual void SetWidgetControllerParams(const FWidgetControllerParams& WCParams) override;
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;
	virtual void UpdateWidget() override;
	UFUNCTION(BlueprintCallable)
	void TransferContent(USlotContainerBaseComponent* FromContainer, int FromIndex, int ToIndex);
	UFUNCTION(BlueprintCallable)
	void ResetQuickSlot(int index);

#pragma region Delegates
	UPROPERTY(BlueprintAssignable)
	FOnInitSlotsSignature OnInitQuickSlotsSignature;

	UPROPERTY(BlueprintAssignable)
	FOnAddSlotSignature OnAddQuickSlotSignature;

	UPROPERTY(BlueprintAssignable)
	FOnResetSlotSignature OnResetQuickSlotSignature;

	UPROPERTY(BlueprintAssignable)
	FOnUpdateAllQuickSlotsSignature OnUpdateAllQuickSlotsSignature;

#pragma endregion

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UQuickSlotComponent> PlayerQuickSlotComponent;

};
