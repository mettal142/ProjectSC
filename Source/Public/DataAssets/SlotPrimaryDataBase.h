// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "SCTypes/SCStructTypes.h"
#include "SCTypes/SCEnumTypes.h"

#include "SlotPrimaryDataBase.generated.h"

class USCGameplayAbility;

/**
 * 
 */
UCLASS()
class PROJECTSC_API USlotPrimaryDataBase : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BaseProperties")
	int ID = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BaseProperties")
	UTexture2D* Icon;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BaseProperties")
	FText Name;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BaseProperties")
	FText Description;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BaseProperties")
	FGameplayTag AbilityTag;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BaseProperties")
	EContentType ContentType;


};
