// Fill out your copyright notice in the Description page of Project Settings.


#include "SCDataManager.h"
#include "Engine/DataTable.h"
#include "SCTypes/SCStructTypes.h"

bool USCDataManager::GetItemByID(int Id, FSCItemStructure& OutItem)
{
	check(ItemTable);
	FName RowName = *FString::FromInt(Id);

	if (FSCItemStructure* FoundItem = ItemTable->FindRow<FSCItemStructure>(RowName, ""))
	{
		OutItem = *FoundItem;
		return true;
	}

	return false;
}

bool USCDataManager::GetInventoryRecipeByID(int Id, FCraftingRecipe& OutRecipe)
{
	check(InventoryRecipeTable);
	FName RowName = *FString::FromInt(Id);


	if (FCraftingRecipe* FoundRecipe= InventoryRecipeTable->FindRow<FCraftingRecipe>(RowName, ""))
	{
		OutRecipe = *FoundRecipe;
		return true;
	}

	return false;
}

bool USCDataManager::GetDropItemByID(int Id, FDropTableStructure& OutDropItem)
{
	check(DropTable);
	FName RowName = *FString::FromInt(Id);

	if (FDropTableStructure* FoundDropItem = DropTable->FindRow<FDropTableStructure>(RowName, ""))
	{
		OutDropItem = *FoundDropItem;
		return true;
	}

	return false;
}
