// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AbilityTickTask.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAbilityTickTaskDelegate, float, DeltaTime);


/**
 * 
 */
UCLASS()
class PROJECTSC_API UAbilityTickTask : public UAbilityTask
{
	GENERATED_BODY()

public:
	UAbilityTickTask();
	
	UFUNCTION(BlueprintCallable, Category = "AbilityTask", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "true"))
	static UAbilityTickTask* ExecuteTaskOnTick(UGameplayAbility* OwningAbility);

	virtual void TickTask(float DeltaTime) override;

	UPROPERTY(BlueprintAssignable)
	FOnAbilityTickTaskDelegate OnAbilityTickTaskDelegate;
	
};
