// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameplayTagContainer.h"
#include "SCTypes/SCEnumTypes.h"
#include "SCFunctionLibrary.generated.h"

class USCAbilitySystemComponent;
class UInventoryWidgetController;
class UPawnCombatComponentBase;
class UInGameOverlayWidgetController;
class UDataTable;
/**
 * 
 */
UCLASS()
class PROJECTSC_API USCFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "SC|FunctionLibrary")
	static void AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd);
	UFUNCTION(BlueprintCallable, Category = "SC|FunctionLibrary")
	static void RemoveGameplayTagFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove);


	static bool DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck);

	static UPawnCombatComponentBase* NativeGetPawnCombatComponentFromActor(AActor* InActor);


	UFUNCTION(BlueprintCallable, Category = "SC|FunctionLibrary", meta = (DisplayName = "Get Pawn Combat Component From Actor", ExpandEnumAsExecs = "OutValidType"))
	static UPawnCombatComponentBase* GetPawnCombatComponentFromActor(AActor* InActor, ESCValidType& OutValidType);


};
