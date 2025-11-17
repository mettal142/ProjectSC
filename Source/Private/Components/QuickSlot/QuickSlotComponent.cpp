// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/QuickSlot/QuickSlotComponent.h"
#include "Components/Inventory/InventoryComponent.h"
#include "Characters/SCPlayerCharacter.h"
#include "Player/SCPlayerController.h"
#include "SCTypes/SCStructTypes.h"
#include "AbilitySystem/Abilities/SCGameplayAbility.h"
#include "AbilitySystem/SCAbilitySystemComponent.h"
#include "DataAssets/Items/ConsumableItemInfo.h"
#include "SCGameplayTags.h"
#include "SCDebugHelper.h"
#include "Net/UnrealNetwork.h"

UQuickSlotComponent::UQuickSlotComponent()
{
	ContainerType = EContainerType::QuickSlot;
	SetIsReplicatedByDefault(true);

}

void UQuickSlotComponent::BeginPlay()
{
	Super::BeginPlay();
	
	
    AActor* Owner = GetOwner();
    if (!IsValid(Owner)) { return; }

    if (const APawn* Pawn = Cast<APawn>(Owner))
    {
        if (!Pawn->IsLocallyControlled()) { return; }
    }


	ASCPlayerCharacter* Player = Cast<ASCPlayerCharacter>(GetOwner());
	check(Player);
	PlayerInventoryComponent = Player->GetInventoryComponent();

	PlayerInventoryComponent->UpdateItemNumberSignature.AddDynamic(this, &UQuickSlotComponent::OnItemNumberUpdated);
	
	Player->GetController<ASCPlayerController>()->ActiveQuickSlotActionSignature.BindLambda([this](int SlotIndex) {
		ActiveSlotAbility(SlotIndex);
	});

}

void UQuickSlotComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UQuickSlotComponent, Slots, COND_None, REPNOTIFY_Always);

}

void UQuickSlotComponent::OnRep_Slots()
{
	UpdateAllQuickSlotsSignature.ExecuteIfBound(Slots);

}

bool UQuickSlotComponent::IsSlotEmpty(int SlotIndex)
{
	return false;
}

int UQuickSlotComponent::FindEmptySlot()
{
	return 0;
}

void UQuickSlotComponent::GenerateDefaultSlots_Implementation()
{
	Slots.Empty();
	for (int i = 0; i < NumOfSlots; i++)
	{
		Slots.Add(FQuickSlotStructure());
		AddSlotSignature.ExecuteIfBound();

	}
	InitSlotsSignature.ExecuteIfBound(NumOfSlots);
}

void UQuickSlotComponent::RemoveContentToIndex_Implementation(int index)
{
	Slots[index].ContentAsset = nullptr;
	Slots[index].ContentType = EContentType::Empty;
	ResetSlotSignature.ExecuteIfBound(index);
}

void UQuickSlotComponent::TransferContent_Implementation(USlotContainerBaseComponent* FromComponent, int FromIndex, int ToIndex)
{
	if (FromComponent->ContainerType == EContainerType::Inventory)
	{
		UInventoryComponent* InventoryComponent = CastChecked<UInventoryComponent>(FromComponent);

		USlotPrimaryDataBase* SlotData = InventoryComponent->GetItemDataAtIndex(FromIndex).LoadSynchronous();
		
		if (SlotData)
		{
			Slots[ToIndex].ContentSlotIndex = FromIndex;
			Slots[ToIndex].ContentID = SlotData->ID;
			Slots[ToIndex].ContentAsset = InventoryComponent->GetItemDataAtIndex(FromIndex);
			Slots[ToIndex].ContentType = SlotData->ContentType;
			const int count = InventoryComponent->GetItemNumber(SlotData->ID);
			Slots[ToIndex].BottomText = FText::AsNumber(count);
			
		}

	}
	else if (FromComponent->ContainerType == EContainerType::QuickSlot)
	{
		USlotPrimaryDataBase* SlotData = Slots[FromIndex].ContentAsset.LoadSynchronous();

		if (SlotData)
		{
			Slots[ToIndex].ContentSlotIndex = Slots[FromIndex].ContentSlotIndex;
			Slots[FromIndex].ContentSlotIndex = -1;
			Slots[ToIndex].ContentID = Slots[FromIndex].ContentID;
			Slots[ToIndex].ContentAsset = Slots[FromIndex].ContentAsset;
			Slots[ToIndex].ContentType = Slots[FromIndex].ContentType;			
			Slots[ToIndex].BottomText = Slots[FromIndex].BottomText;

			RemoveContentToIndex(FromIndex);		
		}
	}
	UpdateAllQuickSlotsSignature.ExecuteIfBound(Slots);
}

void UQuickSlotComponent::OnItemNumberUpdated(int ItemID, int ItemNum)
{
	
	for (int i = 0; i < Slots.Num(); ++i)
	{
		if (Slots[i].ContentID == ItemID)
		{
			Slots[i].BottomText = FText::AsNumber(ItemNum);

		}
	}
	UpdateAllQuickSlotsSignature.ExecuteIfBound(Slots);
}

void UQuickSlotComponent::ActiveSlotAbility(int SlotIndex)
{
	if (Slots[SlotIndex].ContentType == EContentType::Empty) return;
	
	else if (Slots[SlotIndex].ContentType == EContentType::Skill)
	{

	}
	else if (Slots[SlotIndex].ContentType == EContentType::Weapon)
	{
		if (USlotPrimaryDataBase* LoadedContents = Slots[SlotIndex].ContentAsset.LoadSynchronous())
		{
			PlayerInventoryComponent->ActivateSlotAbility(LoadedContents, Slots[SlotIndex].ContentSlotIndex);
		}
	}
	else
	{
		if (USlotPrimaryDataBase* LoadedContents = Slots[SlotIndex].ContentAsset.LoadSynchronous())
		{
			PlayerInventoryComponent->ActivateSlotAbility(LoadedContents, Slots[SlotIndex].ContentSlotIndex);
		}
	}
	
	UpdateAllQuickSlotsSignature.ExecuteIfBound(Slots);


}

