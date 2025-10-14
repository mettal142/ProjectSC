// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/InventoryWidgetController.h"
#include "Characters/SCPlayerCharacter.h"
#include "Components/Inventory/InventoryComponent.h"
#include "SCTypes/SCStructTypes.h"
#include "DataAssets/Items/BaseItemInfo.h"
#include "SCDebugHelper.h"

void UInventoryWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	Super::SetWidgetControllerParams(WCParams);

	check(WCParams.PlayerController);
	if (ASCPlayerCharacter* Character = Cast<ASCPlayerCharacter>(WCParams.PlayerController->GetPawn()))
	{
		PlayerInventoryComponent = Character->GetInventoryComponent();
	}
	

}

void UInventoryWidgetController::BroadcastInitialValues()
{
	check(PlayerInventoryComponent);

	const TArray<FSCItemStructure>& Items = PlayerInventoryComponent->GetItems();
	int Num = Items.Num();
	OnInitSlotsSignature.Broadcast(Num);
	OnUpdateAllSlotsSignature.Broadcast(Items);
}

void UInventoryWidgetController::BindCallbacksToDependencies()
{
	check(PlayerInventoryComponent);
	PlayerInventoryComponent->InitSlotsSignature.BindLambda([this](int NumOfSlots) {OnInitSlotsSignature.Broadcast(NumOfSlots); });
	PlayerInventoryComponent->AddSlotSignature.BindLambda([this](){OnAddSlotSignature.Broadcast(); });
	PlayerInventoryComponent->UpdateAllSlotsSignature.BindLambda([this](const TArray<FSCItemStructure>& Items) {OnUpdateAllSlotsSignature.Broadcast(Items); });
	PlayerInventoryComponent->ResetSlotSignature.BindLambda([this](int Index) {OnResetSlotSignature.Broadcast(Index); });
	PlayerInventoryComponent->UpdateItemSlotSignature.BindLambda([this](int SlotIndex, const FSCItemStructure& ItemInfo) {OnUpdateItemSlotSignature.Broadcast(SlotIndex, ItemInfo); });
	PlayerInventoryComponent->AddItemSignature.BindLambda([this](const FSCItemStructure& ItemInfo,int ItemNum) {OnAddItemSignature.Broadcast(ItemInfo, ItemNum); });

}

void UInventoryWidgetController::UpdateWidget()
{
	check(PlayerInventoryComponent);

	const TArray<FSCItemStructure>& Items = PlayerInventoryComponent->GetItems();
	OnUpdateAllSlotsSignature.Broadcast(Items);

}

void UInventoryWidgetController::ShowItemDesc(const FSCItemStructure& ItemInfo)
{
	OnShowItemDescSignature.Broadcast(ItemInfo);
}

void UInventoryWidgetController::HideItemDesc()
{
	OnHideItemDescSignature.Broadcast();
}

void UInventoryWidgetController::TransferItem(USlotContainerBaseComponent* FromContainer, int FromIndex, int ToIndex)
{
	PlayerInventoryComponent->TransferContent(FromContainer, FromIndex, ToIndex);

}

void UInventoryWidgetController::UseItem(const FSCItemStructure& SlotItem, int Index)
{
	if (UBaseItemInfo* ItemInfo = SlotItem.ItemAsset.LoadSynchronous())
	{		
		PlayerInventoryComponent->ActivateSlotAbility(ItemInfo, Index);
	}
}

void UInventoryWidgetController::CloseItemMenu()
{
	OnCloseItemMenuSignature.Broadcast();
}

void UInventoryWidgetController::OpenItemMenu(const FSCItemStructure& SlotItem, int Index)
{
	OnOpenItemMenuSignature.Broadcast(Index, SlotItem);
}
