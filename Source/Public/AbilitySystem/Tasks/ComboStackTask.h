// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "Abilities/GameplayAbilityTargetTypes.h"

#include "ComboStackTask.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnComboStackChangedSignature, const FGameplayAbilityTargetDataHandle&, DataHandle);

USTRUCT()
struct FGameplayAbilityTargetData_StackCount : public FGameplayAbilityTargetData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	int32 StackCount = 0;
	virtual UScriptStruct* GetScriptStruct() const override
	{
		return FGameplayAbilityTargetData_StackCount::StaticStruct();
	}

	virtual FString ToString() const override
	{
		return FString::Printf(TEXT("StackCount: %d"), StackCount);
	}

	bool NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess)
	{
		Ar << StackCount;
		bOutSuccess = true;
		return true;
	}
};
template<>
struct TStructOpsTypeTraits<FGameplayAbilityTargetData_StackCount> :
	public TStructOpsTypeTraitsBase2<FGameplayAbilityTargetData_StackCount>
{
	enum { WithNetSerializer = true };
};

/**
 * 
 */
UCLASS()
class PROJECTSC_API UComboStackTask : public UAbilityTask
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (DisplayName = "Apply Combo Stack", HidePin = "OwningAbility", DefaultToSelf = "OwningAbility"))
	static UComboStackTask* ApplyComboStack(UGameplayAbility* OwningAbility, int32 InMaxCombo, TSubclassOf<UGameplayEffect> ComgoGE);

	UFUNCTION(BlueprintPure, Category = "Ability|Tasks")
	static int32 GetComboStackCount(const FGameplayAbilityTargetDataHandle& DataHandle);

	virtual void Activate() override;

	UPROPERTY(BlueprintAssignable)
	FOnComboStackChangedSignature OnStackChangedSignature;

protected:
	void SendPredictedCount();

	TSubclassOf<UGameplayEffect> ComboStackEffectClass;

	void OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle& DataHandle, FGameplayTag ActivationTag);

	int32 MaxCombo = 0;

};
