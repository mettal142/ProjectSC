// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SCDataManager.h"

#include "SCGameInstance.generated.h"


/**
 * 
 */
UCLASS()
class PROJECTSC_API USCGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	virtual void Init() override;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<USCDataManager> DataManager;

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<USCDataManager> DataManagerClass;
};
