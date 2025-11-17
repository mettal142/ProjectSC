// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Inventory/ItemContainerBaseComponent.h"
#include "SCTypes/SCEnumTypes.h"
#include "GameplayTagContainer.h"
#include "InventoryComponent.generated.h"

class USlotPrimaryDataBase;

/**
 * 
 */
UCLASS()
class PROJECTSC_API UInventoryComponent : public UItemContainerBaseComponent
{
	GENERATED_BODY()
	
public:
	UInventoryComponent();

	void ActivateSlotAbility(USlotPrimaryDataBase* SlotData, int SlotIndex = -1 );

	int FindIndexByGuid(FGuid Guid);

};
