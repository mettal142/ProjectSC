// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/SCPlayerGameplayAbility.h"
#include "Characters/SCPlayerCharacter.h"
#include "Player/SCPlayerController.h"
#include "Components/Combat/PlayerCombatComponent.h"

ASCPlayerCharacter* USCPlayerGameplayAbility::GetPlayerCharacterFromActorInfo()
{
    if (!CachedSCPlayerCharacter.IsValid())
    {
        CachedSCPlayerCharacter = Cast<ASCPlayerCharacter>(CurrentActorInfo->AvatarActor);
    }
    return  CachedSCPlayerCharacter.IsValid() ? CachedSCPlayerCharacter.Get() : nullptr;
}

ASCPlayerController* USCPlayerGameplayAbility::GetPlayerControllerFromActorInfo()
{
    if (!CashedSCPlayerController.IsValid())
    {
        CashedSCPlayerController = Cast<ASCPlayerController>(CurrentActorInfo->PlayerController);
    }
    return CashedSCPlayerController.IsValid() ? CashedSCPlayerController.Get() : nullptr;
}

UPlayerCombatComponent* USCPlayerGameplayAbility::GetPlayerCombatComponentFromActorInfo()
{
	return Cast<UPlayerCombatComponent>(GetPlayerCharacterFromActorInfo()->GetPawnCombatComponent());
}

FGameplayEffectSpecHandle USCPlayerGameplayAbility::MakePlayerDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, float InWeaponBaseDamage, FGameplayTag InCurrentAttackTypeTag, int32 InUsedComboCount)
{
	return FGameplayEffectSpecHandle();
}
