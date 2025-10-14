// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/SCWidgetController.h"
#include "SCTypes/SCEnumTypes.h"
#include "MenuWidgetController.generated.h"

class UInventoryWidgetController;
class UCraftingWidgetController;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSwitchWidgetSignature, EMenuType, MenuType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSetVisibilitySignature, ESlateVisibility, Visibility);

/**
 * 
 */
UCLASS()
class PROJECTSC_API UMenuWidgetController : public USCWidgetController
{
	GENERATED_BODY()
public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

	UFUNCTION(BlueprintPure)
	UInventoryWidgetController* GetInventoryWidgetController();

	UFUNCTION(BlueprintPure)
	UCraftingWidgetController* GetCraftingWidgetController();


	UPROPERTY(BlueprintAssignable)
	FOnSwitchWidgetSignature OnSwitchWidget;

	UPROPERTY(BlueprintReadOnly)
	EMenuType CurrentMenuType;

	UPROPERTY(BlueprintAssignable)
	FSetVisibilitySignature OnSetVisibilitySignature;
private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UInventoryWidgetController> InventoryWidgetController;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UInventoryWidgetController> InventoryWidgetControllerClass;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCraftingWidgetController> CraftingWidgetController;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UCraftingWidgetController> CraftingWidgetControllerClass;

};
