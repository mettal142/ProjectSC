// Fill out your copyright notice in the Description page of Project Settings.

#include "SCTypes/SCStructTypes.h"
#include "AbilitySystem/Abilities/SCGameplayAbility.h"

bool FSCCharacterAbilitySet::IsValid() const
{
    return AbilityTag.IsValid() && AbilityToGrant;
}
