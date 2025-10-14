// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/Items/UnequippableItemInfo.h"
#include "ConsumableItemInfo.generated.h"

class UGameplayEffect;

/**
 * 
 */
UCLASS()
class PROJECTSC_API UConsumableItemInfo : public UUnequippableItemInfo
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	TSubclassOf<UGameplayEffect> GameplayEffectClass;
};
