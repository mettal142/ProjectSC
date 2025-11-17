// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Data/CharacterClassInfo.h"
#include "SCAbilitySystemLibrary.generated.h"

class ASCHUD;
class UMenuWidgetController;
class UInGameOverlayWidgetController;
class UQuickSlotWidgetController;
struct FWidgetControllerParams;

/**
 * 
 */
UCLASS()
class PROJECTSC_API USCAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category = "SCAbilitySystemLibrary|WidgetController", meta = (DefaultToSelf = "WorldContextObject"))
	static bool MakeWidgetControllerParams(const UObject* WorldContextObject, FWidgetControllerParams& OutWCParams, ASCHUD*& OutSCHUD);

	UFUNCTION(BlueprintPure, Category = "SCAbilitySystemLibrary|WidgetController", meta = (DefaultToSelf = "WorldContextObject"))
	static UMenuWidgetController* GetMenuWidgetController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "SCAbilitySystemLibrary|WidgetController", meta = (DefaultToSelf = "WorldContextObject"))
	static UInGameOverlayWidgetController* GetInGameOverlayWidgetController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "SCAbilitySystemLibrary|WidgetController", meta = (DefaultToSelf = "WorldContextObject"))
	static UQuickSlotWidgetController* GetQuickSlotWidgetController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "AuraAbilitySystemLibrary|GameplayMechanics", meta = (DefaultToSelf = "WorldContextObject"))
	static void GetLiveCharactersWithinRadius(const UObject* WorldContextObject, TArray<AActor*>& OutOverlappingActors, const TArray<AActor*>& ActorsToIgnore, float Radius, const FVector& SphereOrigin);

	UFUNCTION(BlueprintCallable, Category = "AbilitySystemLibrary|CharacterClassDefaults")
	static void InitializeDefaultAttributes(const UObject* WorldContextObject, ECharacterClass CharacterClass, float Level, UAbilitySystemComponent* ASC);

	UFUNCTION(BlueprintCallable, Category = "AbilitySystemLibrary|CharacterClassDefaults")
	static void ApplyEffectToTargetActor(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass);
	UFUNCTION(BlueprintCallable, Category = "AbilitySystemLibrary|CharacterClassDefaults")
	static UCharacterClassInfo* GetCharacterClassInfo(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "AbilitySystem|Tags")
	static void SetLooseTagCount(UAbilitySystemComponent* ASC, FGameplayTag Tag, int32 NewCount);
};
