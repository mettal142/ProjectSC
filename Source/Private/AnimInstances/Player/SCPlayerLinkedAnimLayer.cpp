// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/Player/SCPlayerLinkedAnimLayer.h"
#include "AnimInstances/Player/SCPlayerAnimInstance.h"

USCPlayerAnimInstance* USCPlayerLinkedAnimLayer::GetPlayerAnimInstance() const
{
    return Cast<USCPlayerAnimInstance>(GetOwningComponent()->GetAnimInstance());
}

int USCPlayerLinkedAnimLayer::SelectPose(FGameplayTag TagToCheck) const
{
    return 0;
}
