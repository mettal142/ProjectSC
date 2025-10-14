// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Data/PlayerStartupData.h"
#include "AbilitySystem/Abilities/SCGameplayAbility.h"
#include "AbilitySystem/SCAbilitySystemComponent.h"

void UPlayerStartupData::GiveToAbilitySystemComponent(USCAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	Super::GiveToAbilitySystemComponent(InASCToGive, ApplyLevel);

	for (const FSCCharacterAbilitySet& AbilitySet : PlayerStartupAbilitySets)
	{
		if (!AbilitySet.IsValid()) continue;

		FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant);
		AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		AbilitySpec.DynamicAbilityTags.AddTag(AbilitySet.AbilityTag);

		InASCToGive->GiveAbility(AbilitySpec);
	}

}
