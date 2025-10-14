// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/Items/BaseItemInfo.h"
#include "WeaponItemInfo.generated.h"

class ASCWeaponBase;
class USCAnimInstanceBase;

/**
 * 
 */
UCLASS()
class PROJECTSC_API UWeaponItemInfo : public UBaseItemInfo
{
	GENERATED_BODY()

public:
	virtual FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId("WeaponItemInfo", GetFName());
	}

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Weapon")
	FGameplayTag WeaponTag;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Weapon")
	TSoftClassPtr<ASCWeaponBase> PlayerWeaponClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Weapon")
	TSoftClassPtr<USCAnimInstanceBase> WeaponAnimLayerToLink;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Weapon")
	TArray<FSCCharacterAbilitySet> DefaultWeaponAbilities;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Weapon")
	TArray<TSoftObjectPtr<UAnimMontage>> AttackMontages;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Weapon")
	FScalableFloat WeaponBaseDamage;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Weapon")
	FGameplayTag EquipSocket;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Weapon")
	FName SocketToEquip;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Weapon")
	FScalableFloat WeaponSpeed = 1.f;

};
