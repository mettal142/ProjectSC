// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/InGameOverlayWidgetController.h"
#include "AbilitySystem/SCAttributeSet.h"
#include "AbilitySystem/SCAbilitySystemComponent.h"

void UInGameOverlayWidgetController::BroadcastInitialValues()
{
	USCAttributeSet* SCAttributeSet = CastChecked<USCAttributeSet>(AttributeSet);
	OnHealthChanged.Broadcast(SCAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(SCAttributeSet->GetMaxHealth());
	OnManaChanged.Broadcast(SCAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(SCAttributeSet->GetMaxMana());
	OnStaminaChanged.Broadcast(SCAttributeSet->GetStamina());
	OnMaxStaminaChanged.Broadcast(SCAttributeSet->GetMaxStamina());
}

void UInGameOverlayWidgetController::BindCallbacksToDependencies()
{
	USCAttributeSet* SCAttributeSet = CastChecked<USCAttributeSet>(AttributeSet);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(SCAttributeSet->GetHealthAttribute()).AddLambda([this](const FOnAttributeChangeData& Data){
		OnHealthChanged.Broadcast(Data.NewValue);
	});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(SCAttributeSet->GetMaxHealthAttribute()).AddLambda([this](const FOnAttributeChangeData& Data) {
		OnMaxHealthChanged.Broadcast(Data.NewValue);
	});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(SCAttributeSet->GetManaAttribute()).AddLambda([this](const FOnAttributeChangeData& Data) {
		OnManaChanged.Broadcast(Data.NewValue);
	});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(SCAttributeSet->GetMaxManaAttribute()).AddLambda([this](const FOnAttributeChangeData& Data) {
		OnMaxManaChanged.Broadcast(Data.NewValue);
	});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(SCAttributeSet->GetStaminaAttribute()).AddLambda([this](const FOnAttributeChangeData& Data) {
		OnStaminaChanged.Broadcast(Data.NewValue);
	});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(SCAttributeSet->GetMaxStaminaAttribute()).AddLambda([this](const FOnAttributeChangeData& Data) {
		OnMaxStaminaChanged.Broadcast(Data.NewValue);
	});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(SCAttributeSet->GetStaminaAttribute()).AddLambda([this](const FOnAttributeChangeData& Data) {
		OnStaminaChanged.Broadcast(Data.NewValue);
	});

}
