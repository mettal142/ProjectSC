// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GameplayEffects/ComboCountEffects.h"
#include "SCGameplayTags.h"

UComboCountEffects::UComboCountEffects()
{
	DurationPolicy = EGameplayEffectDurationType::Infinite;

	StackingType = EGameplayEffectStackingType::AggregateByTarget;
	StackLimitCount = 99;

	StackDurationRefreshPolicy = EGameplayEffectStackingDurationPolicy::NeverRefresh;
	StackPeriodResetPolicy = EGameplayEffectStackingPeriodPolicy::NeverReset;

	InheritableOwnedTagsContainer.AddTag(FSCGameplayTags::Get().Shared_State_ComboCount);
}
