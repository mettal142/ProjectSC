// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/SCWidgetController.h"
#include "InventoryWidgetController.generated.h"


struct FSCItemStructure;
class UInventoryComponent;
class USlotContainerBaseComponent;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpdateAllItemSlotsSignature, const TArray<FSCItemStructure>&, Items);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnShowItemDescSignature, const FSCItemStructure&, ItemInfo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnUpdateItemSlotSignature, int, SlotIndex, const FSCItemStructure&, ItemInfo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnOpenItemMenuSignature, int, SlotIndex, const FSCItemStructure&, ItemInfo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAddItemSignature, const FSCItemStructure&, ItemInfo, int, ItemNum);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCloseItemMenuSignature);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHideItemDescSignature);


/**
 * 
 */
UCLASS()
class PROJECTSC_API UInventoryWidgetController : public USCWidgetController
{
	GENERATED_BODY()
	
public:
	virtual void SetWidgetControllerParams(const FWidgetControllerParams& WCParams) override;
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;
	virtual void UpdateWidget() override;

	UFUNCTION(BlueprintCallable)
	void ShowItemDesc(const FSCItemStructure& ItemInfo);

	UFUNCTION(BlueprintCallable)
	void HideItemDesc();

	UFUNCTION(BlueprintCallable)
	void TransferItem(USlotContainerBaseComponent* FromContainer, int FromIndex, int ToIndex);

	UFUNCTION(BlueprintCallable)
	void UseItem(const FSCItemStructure& SlotItem, int Index);

	UFUNCTION(BlueprintCallable)
	void OpenItemMenu(const FSCItemStructure& SlotItem, int Index);
		
	UFUNCTION(BlueprintCallable)
	void CloseItemMenu();


	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UInventoryComponent> PlayerInventoryComponent;

#pragma region Delegates
	UPROPERTY(BlueprintAssignable)
	FOnInitSlotsSignature OnInitSlotsSignature;

	UPROPERTY(BlueprintAssignable)
	FOnAddSlotSignature OnAddSlotSignature;

	UPROPERTY(BlueprintAssignable)
	FOnUpdateAllItemSlotsSignature OnUpdateAllSlotsSignature;

	UPROPERTY(BlueprintAssignable)
	FOnResetSlotSignature OnResetSlotSignature;

	UPROPERTY(BlueprintAssignable)
	FOnShowItemDescSignature OnShowItemDescSignature;

	UPROPERTY(BlueprintAssignable)
	FOnHideItemDescSignature OnHideItemDescSignature;

	UPROPERTY(BlueprintAssignable)
	FOnUpdateItemSlotSignature OnUpdateItemSlotSignature;

	UPROPERTY(BlueprintAssignable)
	FOnOpenItemMenuSignature OnOpenItemMenuSignature;
	
	UPROPERTY(BlueprintAssignable)
	FOnCloseItemMenuSignature OnCloseItemMenuSignature;

	UPROPERTY(BlueprintAssignable)
	FOnAddItemSignature OnAddItemSignature;
#pragma endregion


};
