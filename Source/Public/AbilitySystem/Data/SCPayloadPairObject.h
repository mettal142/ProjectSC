// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SCPayloadPairObject.generated.h"

class USlotPrimaryDataBase;

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class PROJECTSC_API USCPayloadPairObject : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<USlotPrimaryDataBase> DataAsset;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FGuid ItemGuid;

};
