// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "SCTypes/SCEnumTypes.h"
#include "SCGameplayAbility.generated.h"


class UPawnCombatComponentBase;
class USCAbilitySystemComponent;

UENUM(BlueprintType)
enum class ESCAbilityActivationPolicy : uint8
{
	OnTriggered,
	OnGiven
};

/**
 * 
 */
UCLASS()
class PROJECTSC_API USCGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
public:
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	
	UPROPERTY(EditDefaultsOnly, Category = "SC|Ability")
	ESCAbilityActivationPolicy AbilityActivationPolicy = ESCAbilityActivationPolicy::OnTriggered;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	FGameplayTag StartupInputTag;

	UFUNCTION(BlueprintPure, Category = "SC|Ability")
	UPawnCombatComponentBase* GetPawnCombatComponentFromActorInfo() const;

	UFUNCTION(BlueprintPure, Category = "SC|Ability")
	USCAbilitySystemComponent* GetSCAbilitySystemComponentFromActorInfo() const;

	FActiveGameplayEffectHandle NativeApplySpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle);

	UFUNCTION(BlueprintCallable, Category = "Warrior|Ability", meta = (DisplayName = "Apply Gameplay Effect Spec Handle To Target Actor", ExpandEnumAsExecs = "OutSuccessType"))
	FActiveGameplayEffectHandle BP_ApplySpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle, ESCSuccessType& OutSuccessType);


};
