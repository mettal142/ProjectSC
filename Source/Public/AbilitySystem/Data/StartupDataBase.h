// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "StartupDataBase.generated.h"

class UGameplayAbility;
class USCAbilitySystemComponent;
class UGameplayEffect;
class USCAnimInstanceBase;

class UWeaponItemInfo;

class UAnimMontage;
class UNiagaraSystem;

/**
 * 
 */
UCLASS()
class PROJECTSC_API UStartupDataBase : public UDataAsset
{
	GENERATED_BODY()
	
public:
	virtual void GiveToAbilitySystemComponent(USCAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1);
	virtual void ApplyEffectToCharacter(APawn* OwnerPawn, USCAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "StartupData")
	TSoftClassPtr<USCAnimInstanceBase> DefaultAnimLayerToLink;

	UPROPERTY(EditAnywhere, Category = "StartupData")
	TArray<TSoftObjectPtr<UAnimMontage>> LightAttackMontages;
	
	UPROPERTY(EditAnywhere, Category = "StartupData")
	TArray<TSoftObjectPtr<UAnimMontage>> HeavyAttackMontages;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "StartupData")
	TArray<TSubclassOf<UGameplayAbility>> ActivateOnGivenAbilities;
	UPROPERTY(EditDefaultsOnly, Category = "StartupData")
	TArray<TSubclassOf<UGameplayAbility>> ReactiveAbilities;
	UPROPERTY(EditDefaultsOnly, Category = "StartupData")
	TArray<TSubclassOf<UGameplayEffect>> StartupGameplayEffects;


};
