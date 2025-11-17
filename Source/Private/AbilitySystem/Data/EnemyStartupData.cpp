// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Data/EnemyStartupData.h"
#include "AbilitySystem/SCAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/SCGameplayAbility.h"

void UEnemyStartupData::GiveToAbilitySystemComponent(USCAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	Super::GiveToAbilitySystemComponent(InASCToGive, ApplyLevel);

}
