// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Tasks/ComboStackTask.h"
#include "AbilitySystemComponent.h"

UComboStackTask* UComboStackTask::ApplyComboStack(UGameplayAbility* OwningAbility,int32 InMaxCombo, TSubclassOf<UGameplayEffect> ComgoGE)
{
	UComboStackTask* MyTask = NewAbilityTask<UComboStackTask>(OwningAbility);
    MyTask->MaxCombo = InMaxCombo;
	MyTask->ComboStackEffectClass = ComgoGE;
	return MyTask;
}

int32 UComboStackTask::GetComboStackCount(const FGameplayAbilityTargetDataHandle& DataHandle)
{
    if (DataHandle.Num() > 0)
    {
        if (const FGameplayAbilityTargetData_StackCount* StackData =
            static_cast<const FGameplayAbilityTargetData_StackCount*>(DataHandle.Get(0)))
        {
            return StackData->StackCount;
        }
    }
    return 0;
}


void UComboStackTask::Activate()
{
    const bool bIsLocallyControlled = Ability->GetCurrentActorInfo()->IsLocallyControlled();
    if (bIsLocallyControlled)
    {
        SendPredictedCount();
    }
    else
    {
        const FGameplayAbilitySpecHandle SpecHandle = GetAbilitySpecHandle();
        const FPredictionKey ActivationPredictionKey = GetActivationPredictionKey();
        AbilitySystemComponent.Get()->AbilityTargetDataSetDelegate(GetAbilitySpecHandle(), GetActivationPredictionKey()).AddUObject(this, &UComboStackTask::OnTargetDataReplicatedCallback);
        const bool bCalledDelegate = AbilitySystemComponent.Get()->CallReplicatedTargetDataDelegatesIfSet(SpecHandle, ActivationPredictionKey);
        if (!bCalledDelegate)
        {
            SetWaitingOnRemotePlayerData();
        }

    }
}

void UComboStackTask::SendPredictedCount()
{
    FScopedPredictionWindow ScopedPrediction(AbilitySystemComponent.Get());

    FGameplayAbilityTargetDataHandle DataHandle;
    FGameplayAbilityTargetData_StackCount* Data = new FGameplayAbilityTargetData_StackCount();

    Data->StackCount = AbilitySystemComponent->GetGameplayEffectCount(ComboStackEffectClass, AbilitySystemComponent.Get());

    DataHandle.Add(Data);
    AbilitySystemComponent->ServerSetReplicatedTargetData(
        GetAbilitySpecHandle(),
        GetActivationPredictionKey(),
        DataHandle,
        FGameplayTag(),
        AbilitySystemComponent->ScopedPredictionKey);

    if (ShouldBroadcastAbilityTaskDelegates())
    {
        OnStackChangedSignature.Broadcast(DataHandle);
    }
}

void UComboStackTask::OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle& DataHandle, FGameplayTag ActivationTag)
{
    AbilitySystemComponent->ConsumeClientReplicatedTargetData(GetAbilitySpecHandle(), GetActivationPredictionKey());
    if (ShouldBroadcastAbilityTaskDelegates())
    {
        OnStackChangedSignature.Broadcast(DataHandle);
    }
}
