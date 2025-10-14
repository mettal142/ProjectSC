// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/SCAnimInstanceBase.h"
#include "SCFunctionLibrary.h"

bool USCAnimInstanceBase::DoesOwnerHaveTag(FGameplayTag TagToCheeck) const
{
    if (APawn* OwningPawn = TryGetPawnOwner())
    {
        return USCFunctionLibrary::DoesActorHaveTag(OwningPawn, TagToCheeck);
    }
    return false;
}
