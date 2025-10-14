// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnExtensionComponentBase.h"
#include "SCTypes/SCEnumTypes.h"

#include "SlotContainerBaseComponent.generated.h"

DECLARE_DELEGATE_OneParam(FInitSlotsSignature, int);
DECLARE_DELEGATE(FAddSlotSignature);
DECLARE_DELEGATE_OneParam(FResetSlotSignature, int);
/**
 * 
 */
UCLASS()
class PROJECTSC_API USlotContainerBaseComponent : public UPawnExtensionComponentBase
{
	GENERATED_BODY()
public:
	USlotContainerBaseComponent();

	virtual bool IsSlotEmpty(int SlotIndex);
	virtual int FindEmptySlot();

	UFUNCTION(BlueprintCallable, Server, Reliable)
	virtual void GenerateDefaultSlots();

	UFUNCTION(Server, Reliable)
	virtual void RemoveContentToIndex(int index);

	UFUNCTION(BlueprintCallable, Server, Reliable)
	virtual void TransferContent(USlotContainerBaseComponent* FromComponent, int FromIndex, int ToIndex);

	FInitSlotsSignature InitSlotsSignature;
	FAddSlotSignature AddSlotSignature;
	FResetSlotSignature ResetSlotSignature;

	int NumOfSlots = 0;
	EContainerType ContainerType;


};
