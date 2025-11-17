// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SlotContainerBaseComponent.h"
#include "QuickSlotComponent.generated.h"

struct FQuickSlotStructure;
struct FWidgetControllerParams;
class ASCPlayerCharacter;
class UInventoryComponent;

DECLARE_DELEGATE_OneParam(FUpdateAllQuickSlotsSignature, const TArray<FQuickSlotStructure>&);


/**
 * 
 */
UCLASS()
class PROJECTSC_API UQuickSlotComponent : public USlotContainerBaseComponent
{
	GENERATED_BODY()

public:
	UQuickSlotComponent();
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

#pragma region FromSlotContainerBase
	virtual bool IsSlotEmpty(int SlotIndex) override;
	virtual int FindEmptySlot() override;
	virtual void GenerateDefaultSlots_Implementation() override;
	virtual void RemoveContentToIndex_Implementation(int index) override;
	virtual void TransferContent_Implementation(USlotContainerBaseComponent* FromComponent, int FromIndex, int ToIndex);
#pragma endregion
	inline TArray<FQuickSlotStructure>& GetSlots() { return Slots; }
	UFUNCTION()
	void OnItemNumberUpdated(int ItemID, int ItemNum);

	void ActiveSlotAbility(int SlotIndex);

#pragma region Delegates
	FUpdateAllQuickSlotsSignature UpdateAllQuickSlotsSignature;

#pragma endregion

	UPROPERTY(ReplicatedUsing = OnRep_Slots)
	TArray<FQuickSlotStructure> Slots;

	UFUNCTION()
	void OnRep_Slots();
	UPROPERTY()
	TObjectPtr<UInventoryComponent> PlayerInventoryComponent;
};
