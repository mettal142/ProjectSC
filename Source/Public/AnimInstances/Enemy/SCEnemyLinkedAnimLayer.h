// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/SCAnimInstanceBase.h"
#include "SCEnemyLinkedAnimLayer.generated.h"

class USCEnemyAnimInstance;

/**
 * 
 */
UCLASS()
class PROJECTSC_API USCEnemyLinkedAnimLayer : public USCAnimInstanceBase
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe))
	USCEnemyAnimInstance* GetEnemyAnimInstance() const;

};
