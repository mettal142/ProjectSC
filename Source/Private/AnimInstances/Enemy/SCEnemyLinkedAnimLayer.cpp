// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/Enemy/SCEnemyLinkedAnimLayer.h"
#include "AnimInstances/Enemy/SCEnemyAnimInstance.h"

USCEnemyAnimInstance* USCEnemyLinkedAnimLayer::GetEnemyAnimInstance() const
{
    return Cast<USCEnemyAnimInstance>(GetOwningComponent()->GetAnimInstance());
}

