// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DestructableActorInfo.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTSC_API UDestructableActorInfo : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	int ActorID;
	int ActorLevel;


};
