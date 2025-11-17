// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/Items/BaseItemInfo.h"
#include "ArmorItemInfo.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTSC_API UArmorItemInfo : public UBaseItemInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Armor")
	TSoftObjectPtr<USkeletalMesh> ArmorMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Armor")
	FGameplayTag EquipSocket;
};
