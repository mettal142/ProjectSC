// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/SCPlayerGameplayAbility.h"

#include "SCDamageGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTSC_API USCDamageGameplayAbility : public USCPlayerGameplayAbility
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void CauseDamage(AActor* TargetActor);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DamageEffectClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
	TMap<FGameplayTag, FScalableFloat> Damages;

	//UFUNCTION(BlueprintPure)
	//FTaggedMontage  GetRandomTaggedMontageFromArray(const TArray<FTaggedMontage>& TaggedMontages) const;


};
