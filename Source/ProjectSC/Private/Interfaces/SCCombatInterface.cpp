// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/SCCombatInterface.h"

// Add default functionality here for any ISCCombatInterface functions that are not pure virtual.

UPawnCombatComponentBase* ISCCombatInterface::GetPawnCombatComponent() const
{
    return nullptr;
}

void ISCCombatInterface::OnHit(AActor* CausedActor)
{
}

void ISCCombatInterface::Die(AActor* CausedActor)
{
}

