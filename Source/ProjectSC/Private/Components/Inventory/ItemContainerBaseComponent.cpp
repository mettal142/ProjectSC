#include "Components/Inventory/ItemContainerBaseComponent.h"
#include "SCTypes/SCStructTypes.h"
#include "Net/UnrealNetwork.h"
#include "DataAssets/Items/BaseItemInfo.h"
#include "SCGameInstance.h"
#include "SCDebugHelper.h"

UItemContainerBaseComponent::UItemContainerBaseComponent()
{
	SetIsReplicatedByDefault(true);
	NumOfSlots = 30;

}
void UItemContainerBaseComponent::BeginPlay()
{
	Super::BeginPlay();


	AActor* Owner = GetOwner();
	if (!IsValid(Owner)) { return; }

	if (const APawn* Pawn = Cast<APawn>(Owner))
	{
		if (!Pawn->IsLocallyControlled()) { return; }
	}

	
}
void UItemContainerBaseComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UItemContainerBaseComponent, Items, COND_None, REPNOTIFY_Always);

}

bool UItemContainerBaseComponent::IsSlotEmpty(int SlotIndex)
{
	return Items[SlotIndex].ItemID == 0;
}
void UItemContainerBaseComponent::GenerateDefaultSlots_Implementation()
{
	Items.Empty();
	for (int i = 0; i < NumOfSlots; i++)
	{
		Items.Add(FSCItemStructure());		
	}
	InitSlotsSignature.ExecuteIfBound(NumOfSlots);
}

int UItemContainerBaseComponent::FindEmptySlot()
{

	for (int i=0; i<Items.Num(); i++)
	{
		if (Items[i].ItemID == 0)
		{
			return i;
		}
	}

	return -1;
}

int UItemContainerBaseComponent::GetItemNumber(int ItemID)
{
	//UE_LOG(LogTemp, Warning, TEXT("this=%p, IsValid=%d, ItemQuantities.Num=%d"),this, IsValid(this), ItemQuantities.Num());
	return ItemQuantities.FindRef(ItemID);
}



void UItemContainerBaseComponent::AddItemToEmptySlot(const FSCItemStructure& InItem)
{
	int EmptySlot = FindEmptySlot();

	if (EmptySlot >= 0)
	{
		Items[EmptySlot] = InItem;
		UpdateItemSlotSignature.ExecuteIfBound(EmptySlot, Items[EmptySlot]);

	}
}

void UItemContainerBaseComponent::UpdateItemQuantities()
{
	ItemQuantities.Empty();

	for (const FSCItemStructure& Item : Items)
	{
		if (Item.ItemID == 0) continue;
		ItemQuantities.FindOrAdd(Item.ItemID) += Item.ItemQuantity;
		UpdateItemNumberSignature.Broadcast(Item.ItemID, ItemQuantities.FindRef(Item.ItemID));
	}
}

TSoftObjectPtr<UBaseItemInfo> UItemContainerBaseComponent::GetItemDataAtIndex(int index)
{
	return Items[index].ItemAsset;
}

TArray<int> UItemContainerBaseComponent::FindItemIndexesByID(int ItemID)
{
	TArray<int> ItemIndexes;

	for (int i = 0; i < Items.Num(); i++)
	{
		if (Items[i].ItemID == ItemID)
		{
			ItemIndexes.AddUnique(i);
		}
	}

	return ItemIndexes;
}

void UItemContainerBaseComponent::RemoveItems_Implementation(int ItemID, int Num)
{
	//Have To Check Number of Item Before Use This Method.
	TArray<int> ItemIndexes = FindItemIndexesByID(ItemID);

	int RemainToRemove = Num;

	for (const int ItemIndex : ItemIndexes)
	{
		if (Items[ItemIndex].ItemQuantity <= RemainToRemove)
		{
			RemainToRemove -= Items[ItemIndex].ItemQuantity;
			RemoveContentToIndex(ItemIndex);
			ResetSlotSignature.ExecuteIfBound(ItemIndex);

		}
		else
		{
			Items[ItemIndex].ItemQuantity -= RemainToRemove;
			RemainToRemove = 0;
			UpdateItemSlotSignature.ExecuteIfBound(ItemIndex, Items[ItemIndex]);

			break;
		}
		
	}

	//UpdateAllSlotsSignature.ExecuteIfBound(Items);
	UpdateItemQuantities();
}

void UItemContainerBaseComponent::UnlockRecipe(int RecipeID)
{
	FCraftingRecipe Recipe;
	
	if (CastChecked<USCGameInstance>(GetWorld()->GetGameInstance())->DataManager->GetInventoryRecipeByID(RecipeID, Recipe))
	{
		UnlockedRecipes.Add(Recipe);
		UpdateCraftableItemsSignature.ExecuteIfBound(UnlockedRecipes);
	}
}

void UItemContainerBaseComponent::OnRep_Items()
{
	UpdateItemQuantities();
	UpdateAllSlotsSignature.ExecuteIfBound(Items);
}

void UItemContainerBaseComponent::RemoveContentToIndex_Implementation(int index)
{
	UpdateItemNumberSignature.Broadcast(Items[index].ItemID, 0);
	Items[index] = FSCItemStructure();	
	ResetSlotSignature.ExecuteIfBound(index);
}

void UItemContainerBaseComponent::TransferContent_Implementation(USlotContainerBaseComponent* FromComponent, int FromIndex, int ToIndex)
{
	if (this == FromComponent && FromIndex == ToIndex) return;
	if (IsSlotEmpty(FromIndex)) return;	
	checkf(FromComponent, TEXT("ToComponent Is Invalid"));

	if (UItemContainerBaseComponent* FromItemContainer = Cast<UItemContainerBaseComponent>(FromComponent))
	{
		if (IsSlotEmpty(ToIndex))
		{
			Items[ToIndex] = FromItemContainer->GetItemAtIndex(FromIndex);
			FromItemContainer->GetItemAtIndex(FromIndex) = FSCItemStructure();
			FromItemContainer->ResetSlotSignature.ExecuteIfBound(FromIndex);
			

		}
		else
		{		
			//swap ·ÎÁ÷
		}
		//FromItemContainer->UpdateAllSlotsSignature.ExecuteIfBound(FromItemContainer->Items);
		//UpdateAllSlotsSignature.ExecuteIfBound(Items);

		UpdateItemQuantities();
		FromItemContainer->UpdateItemSlotSignature.ExecuteIfBound(FromIndex, FromItemContainer->GetItemAtIndex(FromIndex));
		UpdateItemSlotSignature.ExecuteIfBound(ToIndex, Items[ToIndex]);


	}

}


void UItemContainerBaseComponent::CreateAddItemNotification_Implementation(const FSCItemStructure& InItem)
{
	AddItemSignature.ExecuteIfBound(InItem, GetItemNumber(InItem.ItemID));

}

void UItemContainerBaseComponent::ServerAddItem_Implementation(const FSCItemStructure& InItem)
{
	if (InItem.bIsStackable)
	{
		TArray<int> ItemIndexes = FindItemIndexesByID(InItem.ItemID);
		FSCItemStructure ItemToAdd = InItem;

		for (int index : ItemIndexes)
		{
			int RemainingStackSize = Items[index].StackSize - Items[index].ItemQuantity;
			if (RemainingStackSize > 0)
			{
				if (RemainingStackSize >= ItemToAdd.ItemQuantity)
				{
					Items[index].ItemQuantity += ItemToAdd.ItemQuantity;
					ItemToAdd.ItemQuantity = 0;
				}
				else
				{
					Items[index].ItemQuantity = Items[index].StackSize;
					ItemToAdd.ItemQuantity -= RemainingStackSize;
					//ResetSlotSignature.ExecuteIfBound(index);
				}
				UpdateItemSlotSignature.ExecuteIfBound(index, Items[index]);

			}

			if (ItemToAdd.ItemQuantity <= 0)
			{
				break;
			}

		}

		if (ItemToAdd.ItemQuantity > 0)
		{
			AddItemToEmptySlot(ItemToAdd);
		}

	}
	else
	{
		AddItemToEmptySlot(InItem);
	}
	CreateAddItemNotification(InItem);
	//UpdateAllSlotsSignature.ExecuteIfBound(Items);
	UpdateItemQuantities();
}

bool UItemContainerBaseComponent::CanCraft(const FCraftingRecipe& ItemRecipe)
{
	bool IsCraftable = true;
	for (const FCraftingMaterial& Mat : ItemRecipe.RequiredItems)
	{

		if (UBaseItemInfo* MatAsset = Mat.ItemAsset.LoadSynchronous())
		{
			if (GetItemNumber(MatAsset->ID) < Mat.Quantity)
			{
				IsCraftable = false;
				break;
			}
		}
		
	}

	return IsCraftable;
}



void UItemContainerBaseComponent::CraftItem_Implementation(const FCraftingRecipe& ItemRecipe)
{
	if (!CanCraft(ItemRecipe)) return;
	
	for (const FCraftingMaterial& ItemToRemove : ItemRecipe.RequiredItems)
	{
		if (UBaseItemInfo* MatAsset = ItemToRemove.ItemAsset.LoadSynchronous())
		{
			RemoveItems(MatAsset->ID, ItemToRemove.Quantity);
		}
	}

	if (const UBaseItemInfo* ResultItem = ItemRecipe.ResultItemAsset.LoadSynchronous())
	{
		FSCItemStructure ItemToAdd;
	
		if (CastChecked<USCGameInstance>(GetWorld()->GetGameInstance())->DataManager->GetItemByID(ResultItem->ID, ItemToAdd))
		{
			ServerAddItem(ItemToAdd);

			UpdateItemQuantities();

			UpdateCraftableItemDescSignature.ExecuteIfBound(ItemRecipe);
			//UpdateAllSlotsSignature.ExecuteIfBound(Items);


		}

	}

}