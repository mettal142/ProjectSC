// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/SCWidgetController.h"
#include "InGameOverlayWidgetController.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangedSignature, float, NewValue);

UCLASS()
class PROJECTSC_API UInGameOverlayWidgetController : public USCWidgetController
{
	GENERATED_BODY()

public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;
	
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnHealthChanged;
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnManaChanged;
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxManaChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnStaminaChanged;
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxStaminaChanged;



};
