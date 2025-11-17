// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SlotContainerBaseComponent.h"
#include "ItemContainerBaseComponent.generated.h"

struct FSCItemStructure;
struct FCraftingRecipe;
class UBaseItemInfo;

DECLARE_DELEGATE_OneParam(FUpdateAllItemSlotsSignature, const TArray<FSCItemStructure>&);
DECLARE_DELEGATE_TwoParams(FUpdateItemSlotSignature, int, const FSCItemStructure&);
DECLARE_DELEGATE_TwoParams(FAddItemSignature, const FSCItemStructure&, int );

DECLARE_DELEGATE_OneParam(FUpdateCraftableItemsSignature, const TArray<FCraftingRecipe>&);
DECLARE_DELEGATE_OneParam(FUpdateCraftableItemDescSignature, const FCraftingRecipe&);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FUpdateItemNumberSignature, int, ItemID, int, ItemNum);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTSC_API UItemContainerBaseComponent : public USlotContainerBaseComponent
{
	GENERATED_BODY()

public:	
	UItemContainerBaseComponent();
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

#pragma region FromSlotContainerBase
	virtual bool IsSlotEmpty(int SlotIndex) override;
	virtual int FindEmptySlot() override;
	virtual void GenerateDefaultSlots_Implementation() override;
	virtual void RemoveContentToIndex_Implementation(int index) override;
	virtual void TransferContent_Implementation(USlotContainerBaseComponent* FromComponent, int FromIndex, int ToIndex) override;
#pragma endregion

#pragma region Get/Set
	UFUNCTION(BlueprintCallable)
	inline TArray<FSCItemStructure>& GetItems() { return Items; }
	inline FSCItemStructure& GetItemAtIndex(int Index) { return Items[Index]; }
	UFUNCTION(BlueprintCallable)
	inline EContainerType GetContainerType(){ return ContainerType; }
	UFUNCTION(BlueprintCallable)
	TSoftObjectPtr<UBaseItemInfo> GetItemDataAtIndex(int index);
#pragma endregion
	UFUNCTION(Server, Reliable)
	void RemoveItems(int ItemID, int Num);

	TArray<int> FindItemIndexesByID(int ItemID);

	int GetItemNumber(int ItemID);

	bool CanCraft(const FCraftingRecipe& ItemRecipe);

	UFUNCTION(BlueprintCallable ,Server,Reliable)
	void ServerAddItem(const FSCItemStructure& InItem);

	UFUNCTION(Client, Reliable)
	void CreateAddItemNotification(const FSCItemStructure& InItem);


	UFUNCTION(BlueprintCallable, Server, Reliable)
	void CraftItem(const FCraftingRecipe& ItemRecipe);


	UFUNCTION(BlueprintCallable)
	void UnlockRecipe(int RecipeID);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FCraftingRecipe> UnlockedRecipes;

#pragma region Delegates
	FUpdateAllItemSlotsSignature UpdateAllSlotsSignature;
	FUpdateCraftableItemsSignature UpdateCraftableItemsSignature;
	FUpdateCraftableItemDescSignature UpdateCraftableItemDescSignature;
	FUpdateItemNumberSignature UpdateItemNumberSignature;
	FUpdateItemSlotSignature UpdateItemSlotSignature;
	FAddItemSignature AddItemSignature;
#pragma endregion

protected:
	void AddItemToEmptySlot(const FSCItemStructure& InItem);
	void UpdateItemQuantities();

	UPROPERTY(ReplicatedUsing = OnRep_Items)
	TArray<FSCItemStructure> Items;

	UPROPERTY(Transient)
	TMap<int, int> ItemQuantities;

	UFUNCTION()
	void OnRep_Items();


};
