// Fill out your copyright notice in the Description page of Project Settings.


#include "SCFunctionLibrary.h"
#include "AbilitySystemGlobals.h"
#include "UI/HUD/SCHUD.h"
#include "Kismet/GameplayStatics.h"
#include "Player/SCPlayerState.h"
#include "UI/WidgetController/InventoryWidgetController.h"
#include "UI/WidgetController/MenuWidgetController.h"
#include "UI/WidgetController/InGameOverlayWidgetController.h"
#include "AbilitySystem/SCAbilitySystemComponent.h"
#include "Components/Combat/PawnCombatComponentBase.h"
#include "Interfaces/SCCombatInterface.h"


void USCFunctionLibrary::AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd)
{
	USCAbilitySystemComponent* ASC = CastChecked<USCAbilitySystemComponent>(UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(InActor));
	
	if (!ASC->HasMatchingGameplayTag(TagToAdd))
	{
		ASC->AddLooseGameplayTag(TagToAdd);
	}
}

void USCFunctionLibrary::RemoveGameplayTagFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove)
{
	USCAbilitySystemComponent* ASC = CastChecked<USCAbilitySystemComponent>(UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(InActor));
	
	if (ASC->HasMatchingGameplayTag(TagToRemove))
	{
		ASC->RemoveLooseGameplayTag(TagToRemove);
	}
}
//
//UInventoryWidgetController* USCFunctionLibrary::GetInventoryWidgetController(const UObject* WorldContextObject)
//{
//	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject,0))
//	{
//		if (ASCHUD* SCHUD = Cast<ASCHUD>(PC->GetHUD()))
//		{
//			ASCPlayerState* PS = PC->GetPlayerState<ASCPlayerState>();
//			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
//			UAttributeSet* AS = PS->GetAttributeSet();
//			const FWidgetControllerParams WidgetConktrollerParams(PC, PS, ASC, AS);
//			return SCHUD->GetMenuWidgetController(WidgetControllerParams)->GetInventoryWidgetController(WidgetControllerParams);
//		}
//	}
//	return nullptr;
//}


bool USCFunctionLibrary::DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck)
{
	if (InActor) return false;
	USCAbilitySystemComponent* ASC = CastChecked<USCAbilitySystemComponent>(UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(InActor));
	return ASC->HasMatchingGameplayTag(TagToCheck);
}

UPawnCombatComponentBase* USCFunctionLibrary::NativeGetPawnCombatComponentFromActor(AActor* InActor)
{
	if (!InActor) return nullptr;
	if (ISCCombatInterface* SCCombatInterface = Cast<ISCCombatInterface>(InActor))
	{
		return SCCombatInterface->GetPawnCombatComponent();
	}
	return nullptr;
}

UPawnCombatComponentBase* USCFunctionLibrary::GetPawnCombatComponentFromActor(AActor* InActor, ESCValidType& OutValidType)
{
	UPawnCombatComponentBase* CombatComponent = NativeGetPawnCombatComponentFromActor(InActor);

	OutValidType = CombatComponent ? ESCValidType::Valid : ESCValidType::InValid;
	
	return CombatComponent;
}
