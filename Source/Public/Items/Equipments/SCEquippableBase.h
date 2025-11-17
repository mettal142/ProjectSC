// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/SCItemBase.h"
#include "SCGameplayTags.h"
#include "SCTypes/SCStructTypes.h"
#include "SCEquippableBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTSC_API ASCEquippableBase : public ASCItemBase
{
	GENERATED_BODY()
	
public:
	ASCEquippableBase();

	FSCEquipmentData EquipmentData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Equipments")
	FGameplayTag EquipSocket;

	UPROPERTY(VisibleAnywhere)
	FGuid Guid;
};
