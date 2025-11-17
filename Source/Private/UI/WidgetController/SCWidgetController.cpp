// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/SCWidgetController.h"
#include "UI/Widgets/SCUserWidget.h"
#include "Player/SCPlayerController.h"
#include "Player/SCPlayerState.h"
#include "AbilitySystem/SCAttributeSet.h"
#include "AbilitySystem/SCAbilitySystemComponent.h"

void USCWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	PlayerController = WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
	AbilitySystemComponent = WCParams.AbilitySystemComponent;
	AttributeSet = WCParams.AttributeSet;
}

void USCWidgetController::BroadcastInitialValues()
{

}

void USCWidgetController::BindCallbacksToDependencies()
{
	
}

void USCWidgetController::UpdateWidget()
{
}
