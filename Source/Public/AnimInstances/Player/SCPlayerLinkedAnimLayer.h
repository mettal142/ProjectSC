// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/SCAnimInstanceBase.h"
#include "SCGameplayTags.h"
#include "SCPlayerLinkedAnimLayer.generated.h"

class USCPlayerAnimInstance;


/**
 * 
 */
UCLASS()
class PROJECTSC_API USCPlayerLinkedAnimLayer : public USCAnimInstanceBase
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe))
	USCPlayerAnimInstance* GetPlayerAnimInstance() const;

	UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe))
	int SelectPose(FGameplayTag TagToCheck) const;
};
