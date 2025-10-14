// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Inventory/InventoryComponent.h"
#include "Components/Combat/PawnCombatComponentBase.h"
#include "AbilitySystem/SCAbilitySystemComponent.h"
#include "Items/Equipments/Weapons/SCWeaponBase.h"
#include "DataAssets/Items/WeaponItemInfo.h"
#include "SCFunctionLibrary.h"
#include "Characters/SCPlayerCharacter.h"
#include "SCGameplayTags.h"
#include "DataAssets/SlotPrimaryDataBase.h"
#include "SCDebugHelper.h"

UInventoryComponent::UInventoryComponent()
{
	ContainerType = EContainerType::Inventory;

}
void UInventoryComponent::ActivateSlotAbility(USlotPrimaryDataBase* SlotData, int SlotIndex)
{
	check(SlotData);

	ASCPlayerCharacter* Player = Cast<ASCPlayerCharacter>(GetOwner());
	USCAbilitySystemComponent* ASC = Cast<USCAbilitySystemComponent>(Player->GetAbilitySystemComponent());

	if (SlotData->ContentType == EContentType::ConsumableItem)
	{
		if (SlotIndex >= 0)
		{
			if (Items[SlotIndex].ItemQuantity > 0)
			{
				FSCGenericPayload Payload;
				Payload.SlotPDAPtr = TSoftObjectPtr<USlotPrimaryDataBase>(SlotData);
				ASC->Server_ActivateAbilityByTagWithSourceObject(SlotData->AbilityTag, Payload, false);
				Items[SlotIndex].ItemQuantity--;
				UpdateItemNumberSignature.Broadcast(SlotData->ID, Items[SlotIndex].ItemQuantity);
				UpdateItemSlotSignature.ExecuteIfBound(SlotIndex, Items[SlotIndex]);
				if (Items[SlotIndex].ItemQuantity <= 0)
				{
					RemoveContentToIndex(SlotIndex);
				}
			}
		}
		else
		{
			if (GetItemNumber(SlotData->ID) > 0)
			{
				FSCGenericPayload Payload;
				Payload.SlotPDAPtr = TSoftObjectPtr<USlotPrimaryDataBase>(SlotData);
				ASC->Server_ActivateAbilityByTagWithSourceObject(SlotData->AbilityTag, Payload, false);
				
				UpdateItemNumberSignature.Broadcast(SlotData->ID, GetItemNumber(SlotData->ID) - 1);
				RemoveItems(SlotData->ID, 1);

			}
		}
	}
	else if (SlotData->ContentType == EContentType::Weapon)
	{

		UPawnCombatComponentBase* CombatComponent = USCFunctionLibrary::NativeGetPawnCombatComponentFromActor(Player);
		FSCGenericPayload Payload;
		Payload.SlotPDAPtr = TSoftObjectPtr<USlotPrimaryDataBase>(SlotData);
		
		if (CombatComponent->IsAttacking) return;
		
		if (ASCWeaponBase* Weapon = CombatComponent->GetCharacterCurrentEquippedWeapon())
		{			
			if (Weapon->WeaponGuid == Items[SlotIndex].Guid)
			{
				CombatComponent->UnequipAndDestroyWeapon();
			}
			else
			{
				
				CombatComponent->UnequipAndDestroyWeapon();

				FGuid NewGuid = FGuid::NewGuid();
				Items[SlotIndex].Guid = NewGuid;				
				CombatComponent->SpawnAndEquipWeapon(Cast<UWeaponItemInfo>(SlotData), NewGuid);

			}
		}
		else
		{
			FGuid NewGuid = FGuid::NewGuid();
			Items[SlotIndex].Guid = NewGuid;
			CombatComponent->SpawnAndEquipWeapon(Cast<UWeaponItemInfo>(SlotData), NewGuid);			

		}
		
	}
	else if (SlotData->ContentType == EContentType::Armor)
	{
		if (GetItemNumber(SlotData->ID) > 0)
		{
			FSCGenericPayload Payload;
			Payload.SlotPDAPtr = TSoftObjectPtr<USlotPrimaryDataBase>(SlotData);
			ASC->Server_ActivateAbilityByTagWithSourceObject(SlotData->AbilityTag, Payload, false);
			RemoveItems(SlotData->ID, 1);
		}
	}

	//
	//if (SlotData->ContentType == EContentType::ConsumableItem)
	//{
	//	if (SlotIndex >= 0)
	//	{
	//		if (Items[SlotIndex].ItemQuantity > 0)
	//		{
	//			USCAbilitySystemComponent* ASC = Cast<USCAbilitySystemComponent>(Player->GetAbilitySystemComponent());
	//			ASC->Server_ActivateAbilityByTagWithSourceObject(AbilityTag, SlotData, false);
	//			Items[SlotIndex].ItemQuantity--;				
	//			UpdateItemNumberSignature.Broadcast(SlotData->ID, Items[SlotIndex].ItemQuantity);
	//			UpdateItemSlotSignature.ExecuteIfBound(SlotIndex, Items[SlotIndex]);
	//			if (Items[SlotIndex].ItemQuantity <= 0)
	//			{
	//				RemoveContentToIndex(SlotIndex);
	//			}
	//		}
	//	}
	//	else
	//	{
	//		if (GetItemNumber(SlotData->ID) > 0)
	//		{
	//			USCAbilitySystemComponent* ASC = Cast<USCAbilitySystemComponent>(Player->GetAbilitySystemComponent());
	//			ASC->Server_ActivateAbilityByTagWithSourceObject(AbilityTag, SlotData, false);
	//			UpdateItemNumberSignature.Broadcast(SlotData->ID, GetItemNumber(SlotData->ID) - 1);
	//			RemoveItems(SlotData->ID, 1);

	//		}
	//	}
	//}
	//else if (SlotData->ContentType == EContentType::Weapon)
	//{
	//	
	//	USCAbilitySystemComponent* ASC = Cast<USCAbilitySystemComponent>(Player->GetAbilitySystemComponent());
	//	UPawnCombatComponentBase* CombatComponent = USCFunctionLibrary::NativeGetPawnCombatComponentFromActor(Player);		
	//	UWeaponItemInfo* WeaponInfo = Cast<UWeaponItemInfo>(SlotData);
	//	if (!CombatComponent->IsAttacking)
	//	{
	//		if (ASCWeaponBase* Weapon = CombatComponent->GetCharacterCurrentEquippedWeapon())
	//		{
	//			if (Weapon->WeaponGuid == Items[SlotIndex].Guid)
	//			{
	//				CombatComponent->UnequipAndDestroyWeapon(WeaponInfo);
	//			}
	//			else
	//			{
	//				CombatComponent->UnequipAndDestroyWeapon(WeaponInfo);
	//				
	//				Items[SlotIndex].Guid = FGuid::NewGuid();
	//				CombatComponent->SpawnAndEquipWeapon(WeaponInfo, Items[SlotIndex].Guid);
	//			}
	//		}
	//		else
	//		{
	//			Items[SlotIndex].Guid = FGuid::NewGuid();
	//			CombatComponent->SpawnAndEquipWeapon(WeaponInfo, Items[SlotIndex].Guid);
	//		}
	//	}
	//}
	//else if (SlotData->ContentType == EContentType::Armor)
	//{
	//	if (GetItemNumber(SlotData->ID) > 0)
	//	{
	//		USCAbilitySystemComponent* ASC = Cast<USCAbilitySystemComponent>(Player->GetAbilitySystemComponent());
	//		ASC->Server_ActivateAbilityByTagWithSourceObject(SlotData->AbilityTag, SlotData, false);
	//		RemoveItems(SlotData->ID, 1);
	//	}
	//}
}

int UInventoryComponent::FindIndexByGuid(FGuid Guid)
{
	for (int i = 0; i < Items.Num(); i++)
	{
		if (Items[i].Guid == Guid) return i;		
	}

	return -1;
}
