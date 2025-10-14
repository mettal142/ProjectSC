// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/Items/BaseItemInfo.h"
#include "BuildableItemInfo.generated.h"

class ABuildableItemBase;

/**
 * 
 */
UCLASS()
class PROJECTSC_API UBuildableItemInfo : public UBaseItemInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BuildableProperties")
	TSoftObjectPtr<UStaticMesh> PreviewMesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BuildableProperties")
	TSoftClassPtr<ABuildableItemBase> BuildableItemClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BuildableProperties")
	FVector BoxLocation;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BuildableProperties")
	FVector BoxExtent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BuildableProperties")
	EBuildableType BuildableType;

	TMap<EBuildableType, FString> BuildableTypeString = {
		{ EBuildableType::Foundation,TEXT("Foundation") },
		{ EBuildableType::Wall,  TEXT("Wall") },
		{ EBuildableType::Ceil, TEXT("Ceil") },
		{ EBuildableType::Roof, TEXT("Roof") },
		{ EBuildableType::Stair, TEXT("Stair") },
		{ EBuildableType::Ramp, TEXT("Ramp") },
		{ EBuildableType::Door, TEXT("Door") },
		{ EBuildableType::Window, TEXT("Window") },
		{ EBuildableType::Torch, TEXT("Torch") }
	};
	
};
