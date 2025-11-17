// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Tasks/AbilityTickTask.h"

UAbilityTickTask::UAbilityTickTask()
{
	bTickingTask = true;
}

UAbilityTickTask* UAbilityTickTask::ExecuteTaskOnTick(UGameplayAbility* OwningAbility)
{
	UAbilityTickTask* MyTask = NewAbilityTask<UAbilityTickTask>(OwningAbility);
	return MyTask;
}

void UAbilityTickTask::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);

	if (ShouldBroadcastAbilityTaskDelegates())
	{
		OnAbilityTickTaskDelegate.Broadcast(DeltaTime);
	}
	else
	{
		EndTask();
	}

}
