// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SCDataManager.generated.h"

class UDataTable;
struct FSCItemStructure;
struct FCraftingRecipe;
struct FDropTableStructure;
/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class PROJECTSC_API USCDataManager : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	bool GetItemByID(int Id, FSCItemStructure& OutItem);
	UFUNCTION(BlueprintCallable)
	bool GetInventoryRecipeByID(int Id, FCraftingRecipe& OutRecipe);
	UFUNCTION(BlueprintCallable)
	bool GetDropItemByID(int Id, FDropTableStructure& OutDropItem);



private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UDataTable> ItemTable;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UDataTable> InventoryRecipeTable;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UDataTable> DropTable;



};
