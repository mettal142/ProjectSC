// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/MenuWidgetController.h"
#include "UI/WidgetController/InventoryWidgetController.h"
#include "UI/WidgetController/CraftingWidgetController.h"

void UMenuWidgetController::BroadcastInitialValues()
{

}

void UMenuWidgetController::BindCallbacksToDependencies()
{

}

UInventoryWidgetController* UMenuWidgetController::GetInventoryWidgetController()
{
	if (!InventoryWidgetController)
	{
		check(InventoryWidgetControllerClass);
		InventoryWidgetController = NewObject<UInventoryWidgetController>(this, InventoryWidgetControllerClass);
		FWidgetControllerParams WCParams;
		WCParams.AbilitySystemComponent = this->AbilitySystemComponent;
		WCParams.AttributeSet = this->AttributeSet;
		WCParams.PlayerController = this->PlayerController;
		WCParams.PlayerState = this->PlayerState;
		InventoryWidgetController->SetWidgetControllerParams(WCParams);
		InventoryWidgetController->BindCallbacksToDependencies();
	}

	return InventoryWidgetController;
}

UCraftingWidgetController* UMenuWidgetController::GetCraftingWidgetController()
{
	if (!CraftingWidgetController)
	{
		check(CraftingWidgetControllerClass);
		CraftingWidgetController = NewObject<UCraftingWidgetController>(this, CraftingWidgetControllerClass);
		FWidgetControllerParams WCParams;
		WCParams.AbilitySystemComponent = this->AbilitySystemComponent;
		WCParams.AttributeSet = this->AttributeSet;
		WCParams.PlayerController = this->PlayerController;
		WCParams.PlayerState = this->PlayerState;
		CraftingWidgetController->SetWidgetControllerParams(WCParams);
		CraftingWidgetController->BindCallbacksToDependencies();
	}

	return CraftingWidgetController;
}
