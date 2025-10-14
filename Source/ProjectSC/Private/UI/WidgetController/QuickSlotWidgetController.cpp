// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/QuickSlotWidgetController.h"
#include "Components/QuickSlot/QuickSlotComponent.h"
#include "SCTypes/SCStructTypes.h"
#include "Characters/SCPlayerCharacter.h"

void UQuickSlotWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	Super::SetWidgetControllerParams(WCParams);

	check(WCParams.PlayerController);
	if (ASCPlayerCharacter* Character = Cast<ASCPlayerCharacter>(WCParams.PlayerController->GetPawn()))
	{
		PlayerQuickSlotComponent= Character->GetQuickSlotComponent();
	}
}

void UQuickSlotWidgetController::BroadcastInitialValues()
{
	check(PlayerQuickSlotComponent);
	const TArray<FQuickSlotStructure>& Slots = PlayerQuickSlotComponent->GetSlots();
	int Num = Slots.Num();
	OnInitQuickSlotsSignature.Broadcast(Num);
	OnUpdateAllQuickSlotsSignature.Broadcast(Slots);
}

void UQuickSlotWidgetController::BindCallbacksToDependencies()
{
	check(PlayerQuickSlotComponent);

	PlayerQuickSlotComponent->InitSlotsSignature.BindLambda([this](int NumOfSlots) {OnInitQuickSlotsSignature.Broadcast(NumOfSlots); });
	PlayerQuickSlotComponent->ResetSlotSignature.BindLambda([this](int Index) {OnResetQuickSlotSignature.Broadcast(Index); });
	PlayerQuickSlotComponent->UpdateAllQuickSlotsSignature.BindLambda([this](const TArray<FQuickSlotStructure>& Slots) {OnUpdateAllQuickSlotsSignature.Broadcast(Slots); });
}

void UQuickSlotWidgetController::UpdateWidget()
{
	check(PlayerQuickSlotComponent);
	const TArray<FQuickSlotStructure>& Slots = PlayerQuickSlotComponent->GetSlots();
	OnUpdateAllQuickSlotsSignature.Broadcast(Slots);

}

void UQuickSlotWidgetController::TransferContent(USlotContainerBaseComponent* FromContainer, int FromIndex, int ToIndex)
{
	PlayerQuickSlotComponent->TransferContent(FromContainer, FromIndex, ToIndex);
}

void UQuickSlotWidgetController::ResetQuickSlot(int index)
{
	PlayerQuickSlotComponent->RemoveContentToIndex(index);
}
