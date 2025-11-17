// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SlotContainerBaseComponent.h"

USlotContainerBaseComponent::USlotContainerBaseComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

bool USlotContainerBaseComponent::IsSlotEmpty(int SlotIndex)
{
    return false;
}

int USlotContainerBaseComponent::FindEmptySlot()
{
    return 0;
}

void USlotContainerBaseComponent::TransferContent_Implementation(USlotContainerBaseComponent* FromComponent, int FromIndex, int ToIndex)
{
}

void USlotContainerBaseComponent::GenerateDefaultSlots_Implementation()
{
}

void USlotContainerBaseComponent::RemoveContentToIndex_Implementation(int index)
{
}
