// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WeaponSpawnData.generated.h"

class USlotPrimaryDataBase;


/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class PROJECTSC_API UWeaponSpawnData : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<USlotPrimaryDataBase> WeaponInfo;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGuid WeaponGuid;

};
