// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/CraftingWidgetController.h"
#include "Components/Inventory/ItemContainerBaseComponent.h"
#include "SCTypes/SCStructTypes.h"
void UCraftingWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	Super::SetWidgetControllerParams(WCParams);

	check(WCParams.PlayerController);

	ItemContainerComponent = PlayerController->GetPawn()->GetComponentByClass<UItemContainerBaseComponent>();
		
}

void UCraftingWidgetController::BroadcastInitialValues()
{
	check(ItemContainerComponent);
	OnUpdateCraftableItemsSignature.Broadcast(ItemContainerComponent->UnlockedRecipes);
}

void UCraftingWidgetController::BindCallbacksToDependencies()
{
	check(ItemContainerComponent);

	ItemContainerComponent->UpdateCraftableItemsSignature.BindLambda([this](const TArray<FCraftingRecipe>& UnlockedRecipes) {OnUpdateCraftableItemsSignature.Broadcast(UnlockedRecipes); });
	ItemContainerComponent->UpdateCraftableItemDescSignature.BindLambda([this](const FCraftingRecipe& ShownRecipe) {OnShowCraftableItemDescSignature.Broadcast(ShownRecipe); });
}

int UCraftingWidgetController::GetItemNumberByID(int ItemID)
{
	return ItemContainerComponent->GetItemNumber(ItemID);
}

void UCraftingWidgetController::ShowItemDesc(const FCraftingRecipe& ItemRecipe)
{
	OnShowCraftableItemDescSignature.Broadcast(ItemRecipe);
}

void UCraftingWidgetController::HideItemDesc()
{
	OnHideCraftableItemDesc.Broadcast();
}

void UCraftingWidgetController::CraftItem(const FCraftingRecipe& ItemRecipe)
{
	ItemContainerComponent->CraftItem(ItemRecipe);
}
