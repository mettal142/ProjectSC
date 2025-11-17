// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagContainer.h"
#include "SCTypes/SCStructTypes.h"
#include "SCAbilitySystemComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTags, const FGameplayTagContainer& /*AssetTags*/);
DECLARE_MULTICAST_DELEGATE_OneParam(FAbilitiesGiven, USCAbilitySystemComponent*);
DECLARE_DELEGATE_OneParam(FForEachAbility, const FGameplayAbilitySpec&);


/**
 * 
 */
UCLASS()
class PROJECTSC_API USCAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	void AbilityActorInfoSet();
	void AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>> StartupAbilities, int32 ApplyLevel);
	void AbilityInputTagPressed(const FGameplayTag& InputTag);
	void AbilityInputTagReleased(const FGameplayTag& InputTag);
	void ForEachAbility(const FForEachAbility& Delegate);
	
	UFUNCTION(BlueprintCallable, Category = "SC|Ability")
	bool FindAbilitySpecByTag(const FGameplayTag& AbilityTag, FGameplayAbilitySpec& OutSpec) const;

	UFUNCTION(Server,Reliable)
	void Server_ActivateAbilityByTagWithSourceObject(const FGameplayTag& AbilityTag, const FSCGenericPayload& Payload, bool bAllowRemoteActivation);

	
	UFUNCTION(BlueprintCallable, Category = "SC|Ability")
	bool ActivateAbilityByTagWithSourceObject(const FGameplayTag& AbilityTag, const FSCGenericPayload& Payload, bool bAllowRemoteActivation);

	UFUNCTION(BlueprintCallable, Category = "SC|Ability", meta = (ApplyLevel = "1"))
	void GrantWeaponAbilities(const TArray<FSCCharacterAbilitySet>& InDefaultWeaponAbilities, int32 ApplyLevel, TArray<FGameplayAbilitySpecHandle>& OutGrantedAbilitySpecHandle);

	UFUNCTION(BlueprintCallable, Category = "SC|Ability")
	void RemoveGrantedPlayerWeaponAbilities(UPARAM(ref) TArray<FGameplayAbilitySpecHandle>& InSpecHandlesToRemove);

	static FGameplayTag GetAbilityTagFromSpec(const FGameplayAbilitySpec& AbilitySpec);
	static FGameplayTag GetInputTagFromSpec(const FGameplayAbilitySpec& AbilitySpec);
	UFUNCTION(BlueprintCallable, Category = "SC|Ability")
	void GetAbilityFromAbilityTag(FGameplayTag AbilityTag, FGameplayAbilitySpec& OutAbilitySpec);

	FEffectAssetTags EffectAssetTags;
	FAbilitiesGiven AbilitiesGivenDelegate;
	bool bStartupAbilitiesGiven = false;
protected:
	virtual void OnRep_ActivateAbilities();

	UFUNCTION(Client, Reliable)
	void ClientEffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle);


};
