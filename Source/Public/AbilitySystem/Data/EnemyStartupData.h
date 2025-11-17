// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Data/StartupDataBase.h"
#include "SCTypes/SCStructTypes.h"
#include "EnemyStartupData.generated.h"


/**
 * 
 */
UCLASS()
class PROJECTSC_API UEnemyStartupData : public UStartupDataBase
{
	GENERATED_BODY()

public:
	virtual void GiveToAbilitySystemComponent(USCAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "StartupData")
	TArray<TSoftObjectPtr<UWeaponItemInfo>> DefaultWeapons;

	UPROPERTY(EditDefaultsOnly, Category = "StartupData")
	float MaxWalkSpeed = 300.f;

};
