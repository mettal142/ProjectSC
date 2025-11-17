// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "SCAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTSC_API USCAssetManager : public UAssetManager
{
	GENERATED_BODY()
	
	static USCAssetManager& Get();

protected:
	virtual void StartInitialLoading() override;

};
