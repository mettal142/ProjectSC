// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Data/StartupDataBase.h"
#include "AbilitySystem/Abilities/SCGameplayAbility.h"
#include "AbilitySystem/SCAbilitySystemComponent.h"

void UStartupDataBase::GiveToAbilitySystemComponent(USCAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	check(InASCToGive);
	InASCToGive->AddCharacterAbilities(ActivateOnGivenAbilities, ApplyLevel);
	InASCToGive->AddCharacterAbilities(ReactiveAbilities, ApplyLevel);

}

void UStartupDataBase::ApplyEffectToCharacter(APawn* OwnerPawn, USCAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	check(OwnerPawn);
	check(InASCToGive);

	for (const TSubclassOf<UGameplayEffect>& EffectClass : StartupGameplayEffects)
	{
		if (!EffectClass) continue;
		FGameplayEffectContextHandle ContextHandle = InASCToGive->MakeEffectContext();
		ContextHandle.AddSourceObject(this);		
		const FGameplayEffectSpecHandle SpecHandle = InASCToGive->MakeOutgoingSpec(EffectClass, ApplyLevel, ContextHandle);
		InASCToGive->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), InASCToGive);
	}


}
