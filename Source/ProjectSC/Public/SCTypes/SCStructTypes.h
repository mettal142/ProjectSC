#pragma once
#include "GameplayTagContainer.h"
#include "SCTypes/SCEnumTypes.h"
#include "ScalableFloat.h"
#include "Engine/DataTable.h"
#include "SCStructTypes.generated.h"

class USCPlayerLinkedAnimLayer;
class USCGameplayAbility;
class UInputMappingContext;
class UBaseItemInfo;
class USlotPrimaryDataBase;
class UBuildableItemInfo;


USTRUCT(BlueprintType)
struct FSCGenericPayload
{
	GENERATED_BODY()

	UPROPERTY() 
	TSoftObjectPtr<USlotPrimaryDataBase> SlotPDAPtr;
	UPROPERTY() 
	FGuid ItemGuid;
};


USTRUCT(BlueprintType)
struct FSCCharacterAbilitySet
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag AbilityTag;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<USCGameplayAbility> AbilityToGrant;

	bool IsValid() const;
};
USTRUCT(BlueprintType)
struct FSCEquipmentData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Equipments")
	TObjectPtr<USkeletalMesh> EquipmentMesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Equipments")
	TArray<TObjectPtr<UMaterialInstance>> EquipmentMaterialList;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Equipments")
	FGameplayTag EquipSocket;

};



USTRUCT(BlueprintType)
struct FSCItemStructure : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int ItemID = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int ItemQuantity =  1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bIsStackable = false;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int StackSize = 1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool HasDurability = false;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MaxDurability;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float CurrentDurability;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UBaseItemInfo> ItemAsset = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FGuid Guid;
	
};

USTRUCT(BlueprintType)
struct FCraftingMaterial
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UBaseItemInfo> ItemAsset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int Quantity = 1;
};

USTRUCT(BlueprintType)
struct FCraftingRecipe : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int RecipeID;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int ResultItemID;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UBaseItemInfo> ResultItemAsset = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int ResultCount = 1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FCraftingMaterial> RequiredItems;
};

USTRUCT(BlueprintType)
struct FQuickSlotStructure 
{	
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int ContentID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EContentType ContentType = EContentType::Empty;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<USlotPrimaryDataBase> ContentAsset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText BottomText;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int ContentSlotIndex = -1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float ProgressBarPercent;

};

USTRUCT(BlueprintType)
struct FDropItemStructure 
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float DropChance = 1.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float HeldItemChance = 1.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int MaxAmount = 2;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int MinAmount = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int Amount = 0;

	//Item, ItemNum
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int DropItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UStaticMesh> DropItemMesh;

};


USTRUCT(BlueprintType)
struct FDropTableStructure : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int ID = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FDropItemStructure> DropItems;
};


USTRUCT(BlueprintType)
struct FBuildablesTableStructure : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UBuildableItemInfo> BuildableItem;
};