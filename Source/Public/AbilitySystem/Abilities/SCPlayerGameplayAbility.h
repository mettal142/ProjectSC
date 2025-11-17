// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/SCGameplayAbility.h"
#include "SCPlayerGameplayAbility.generated.h"

class ASCPlayerCharacter;
class ASCPlayerController;
class UPlayerCombatComponent;
/**
 * 
 */
UCLASS()
class PROJECTSC_API USCPlayerGameplayAbility : public USCGameplayAbility
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, Category = "SC|Ability")
	ASCPlayerCharacter* GetPlayerCharacterFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "SC|Ability")
	ASCPlayerController* GetPlayerControllerFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "SC|Ability")
	UPlayerCombatComponent* GetPlayerCombatComponentFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "SC|Ability")
	FGameplayEffectSpecHandle MakePlayerDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, float InWeaponBaseDamage, FGameplayTag InCurrentAttackTypeTag, int32 InUsedComboCount);

private:
	TWeakObjectPtr<ASCPlayerCharacter> CachedSCPlayerCharacter;
	TWeakObjectPtr< ASCPlayerController> CashedSCPlayerController;
};
