// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameplayTagContainer.h"
#include "WeaponDestroyData.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class PROJECTSC_API UWeaponDestroyData : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag EquipSocket;


};
