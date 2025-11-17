// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/Items/BaseItemInfo.h"

#include "BaseArmorInfo.generated.h"

struct FSkeletalMaterial;

/**
 * 
 */
UCLASS()
class PROJECTSC_API UBaseArmorInfo : public UBaseItemInfo
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Armor")
	TObjectPtr<USkeletalMesh> ArmorMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Armor")
	TArray<FSkeletalMaterial> ArmorMaterials;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Armor")
	FGameplayTag EquipSocket;
};
