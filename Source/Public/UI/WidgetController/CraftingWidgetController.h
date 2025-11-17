// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/SCWidgetController.h"
#include "CraftingWidgetController.generated.h"

class UItemContainerBaseComponent;
struct FCraftingRecipe;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpdateCraftableItemsSignature, const TArray<FCraftingRecipe>&, UnlockedRecipes);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnShowCraftableItemDescSignature, const FCraftingRecipe&, ItemRecipe);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHideCraftableItemDesc);
/**
 * 
 */
UCLASS()
class PROJECTSC_API UCraftingWidgetController : public USCWidgetController
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnUpdateCraftableItemsSignature OnUpdateCraftableItemsSignature;
	UPROPERTY(BlueprintAssignable)
	FOnShowCraftableItemDescSignature OnShowCraftableItemDescSignature;
	UPROPERTY(BlueprintAssignable)
	FOnHideCraftableItemDesc OnHideCraftableItemDesc;

	virtual void SetWidgetControllerParams(const FWidgetControllerParams& WCParams) override;

	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

	UFUNCTION(BlueprintPure)
	int GetItemNumberByID(int ItemID);

	UFUNCTION(BlueprintCallable)
	void ShowItemDesc(const FCraftingRecipe& ItemRecipe);

	UFUNCTION(BlueprintCallable)
	void HideItemDesc();

	UFUNCTION(BlueprintCallable)
	void CraftItem(const FCraftingRecipe& ItemRecipe);

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UItemContainerBaseComponent> ItemContainerComponent;
};
