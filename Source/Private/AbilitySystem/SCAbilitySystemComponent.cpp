// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/SCAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/SCGameplayAbility.h"
#include "DataAssets/SlotPrimaryDataBase.h"
#include "AbilitySystem/Data/SCPayloadPairObject.h"
#include "Engine/AssetManager.h"
#include "SCGameplayTags.h"
#include "SCDebugHelper.h"

void USCAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &ThisClass::ClientEffectApplied);
}

void USCAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>> StartupAbilities, int32 ApplyLevel)
{
	for (const TSubclassOf<UGameplayAbility> AbilityClass : StartupAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		if (const USCGameplayAbility* SCAbility = Cast<USCGameplayAbility>(AbilitySpec.Ability))
		{
			AbilitySpec.DynamicAbilityTags.AddTag(SCAbility->StartupInputTag);
			GiveAbility(AbilitySpec);
		}
	}
	bStartupAbilitiesGiven = true;
	AbilitiesGivenDelegate.Broadcast(this);


}

void USCAbilitySystemComponent::AbilityInputTagPressed(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;

	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{	
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			AbilitySpecInputPressed(AbilitySpec);

			if (InputTag.MatchesTag(FSCGameplayTags::Get().InputTag_Toggle))
			{
				if (!AbilitySpec.IsActive())
				{
					TryActivateAbility(AbilitySpec.Handle);
				}
				else
				{
					CancelAbilityHandle(AbilitySpec.Handle);
				}
			}
			else
			{
				if (!AbilitySpec.IsActive())
				{
					TryActivateAbility(AbilitySpec.Handle);
				}
			}
		}
	}
}

void USCAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;


	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTag(InputTag) && AbilitySpec.IsActive())
		{
			AbilitySpecInputReleased(AbilitySpec);

			if (InputTag.MatchesTag(FSCGameplayTags::Get().InputTag_Hold))
			{
				CancelAbilityHandle(AbilitySpec.Handle);

			}
		}
		
	}
}

void USCAbilitySystemComponent::ForEachAbility(const FForEachAbility& Delegate)
{
	FScopedAbilityListLock ActivaScopeLock(*this);
	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (!Delegate.ExecuteIfBound(AbilitySpec))
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to execute delegate in %hs"), __FUNCTION__);

		}
	}
}

bool USCAbilitySystemComponent::FindAbilitySpecByTag(const FGameplayTag& AbilityTag, FGameplayAbilitySpec& OutSpec) const
{
	FScopedAbilityListLock  Lock(const_cast<USCAbilitySystemComponent&>(*this));

	for (const FGameplayAbilitySpec& Spec : GetActivatableAbilities())
	{
		if (!Spec.Ability) continue;

		if (Spec.Ability.Get()->AbilityTags.HasTagExact(AbilityTag))
		{
			OutSpec = Spec;
			return true;
		}
	}
	return false;
}

void USCAbilitySystemComponent::Server_ActivateAbilityByTagWithSourceObject_Implementation(const FGameplayTag& AbilityTag, const FSCGenericPayload& Payload, bool bAllowRemoteActivation)
{
	ActivateAbilityByTagWithSourceObject(AbilityTag, Payload, bAllowRemoteActivation);
}

bool USCAbilitySystemComponent::ActivateAbilityByTagWithSourceObject(const FGameplayTag& AbilityTag, const FSCGenericPayload& Payload, bool bAllowRemoteActivation)
{
	FGameplayAbilitySpec Spec;
	if (!FindAbilitySpecByTag(AbilityTag, Spec))
	{
		return false;
	}

	FGameplayAbilitySpec* SpecPtr = FindAbilitySpecFromHandle(Spec.Handle);
	if (!SpecPtr) return false;


	USCPayloadPairObject* Pair = NewObject<USCPayloadPairObject>(this);
	Pair->DataAsset = Payload.SlotPDAPtr;
	Pair->ItemGuid = Payload.ItemGuid;

	{
		FScopedAbilityListLock Lock(*this);
		SpecPtr->SourceObject = Pair;
		MarkAbilitySpecDirty(*SpecPtr);
	}

	return TryActivateAbility(SpecPtr->Handle);
}

void USCAbilitySystemComponent::GrantWeaponAbilities(const TArray<FSCCharacterAbilitySet>& InDefaultWeaponAbilities, int32 ApplyLevel, TArray<FGameplayAbilitySpecHandle>& OutGrantedAbilitySpecHandle)
{	
	if (InDefaultWeaponAbilities.IsEmpty()) return;

	for (const FSCCharacterAbilitySet& AbilitySet : InDefaultWeaponAbilities)
	{
		if (!AbilitySet.IsValid()) continue;

		FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant);
		AbilitySpec.SourceObject = GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		AbilitySpec.DynamicAbilityTags.AddTag(AbilitySet.AbilityTag);

		OutGrantedAbilitySpecHandle.AddUnique(GiveAbility(AbilitySpec));
	}

}

void USCAbilitySystemComponent::RemoveGrantedPlayerWeaponAbilities(UPARAM(ref)TArray<FGameplayAbilitySpecHandle>& InSpecHandlesToRemove)
{
	if (InSpecHandlesToRemove.IsEmpty())
	{
		return;
	}
	for (const FGameplayAbilitySpecHandle& SpecHandle : InSpecHandlesToRemove)
	{
		if (SpecHandle.IsValid())
		{
			ClearAbility(SpecHandle);
		}
	}

	InSpecHandlesToRemove.Empty();
}


FGameplayTag USCAbilitySystemComponent::GetAbilityTagFromSpec(const FGameplayAbilitySpec& AbilitySpec)
{
	if (AbilitySpec.Ability)
	{
		for (FGameplayTag Tag : AbilitySpec.Ability.Get()->AbilityTags)
		{
			if (Tag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Abilities"))))
			{
				return Tag;
			}
		}

	}
	return FGameplayTag();
}

FGameplayTag USCAbilitySystemComponent::GetInputTagFromSpec(const FGameplayAbilitySpec& AbilitySpec)
{
	return FGameplayTag();
}

void USCAbilitySystemComponent::GetAbilityFromAbilityTag(FGameplayTag AbilityTag, FGameplayAbilitySpec& OutAbilitySpec)
{
	FScopedAbilityListLock ActivaScopeLock(*this);
	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.Ability && AbilitySpec.Ability.Get()->AbilityTags.HasTagExact(AbilityTag))
		{
			OutAbilitySpec = AbilitySpec;
		}
	}
}

void USCAbilitySystemComponent::OnRep_ActivateAbilities()
{
	Super::OnRep_ActivateAbilities();
	if (!bStartupAbilitiesGiven)
	{
		bStartupAbilitiesGiven = true;
		AbilitiesGivenDelegate.Broadcast(this);
	}
}

void USCAbilitySystemComponent::ClientEffectApplied_Implementation(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);

	EffectAssetTags.Broadcast(TagContainer);
}
