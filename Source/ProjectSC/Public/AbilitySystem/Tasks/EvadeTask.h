// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "EvadeTask.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEvadeDataSignature, const FGameplayAbilityTargetDataHandle&, DataHandle);

/**
 * 
 */
UCLASS()
class PROJECTSC_API UEvadeTask : public UAbilityTask
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (DisplayName = "GetEvadeLocation", HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "true"))
	static UEvadeTask* CreateEvateTask(UGameplayAbility* OwningAbility);

	UPROPERTY(BlueprintAssignable)
	FEvadeDataSignature ValidData;

private:
	virtual void Activate() override;
	void SendEvadeLocationData();

	void OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle& DataHandle, FGameplayTag ActivationTag);

};
