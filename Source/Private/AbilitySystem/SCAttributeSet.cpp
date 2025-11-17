// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/SCAttributeSet.h"
#include "GameFramework/Character.h"
#include "SCGameplayTags.h"
#include "GameplayEffectExtension.h"
#include "AbilitySystem/SCAbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Interfaces/SCCombatInterface.h"
#include "Net/UnrealNetwork.h"
#include "SCDebugHelper.h"

USCAttributeSet::USCAttributeSet()
{
	const FSCGameplayTags& GameplayTags = FSCGameplayTags::Get();

	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_HealthRegeneration, GetHealthRegenerationAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_ManaRegeneration, GetManaRegenerationAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_ManaRegeneration, GetStaminaRegenerationAttribute);

	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_MaxHealth, GetMaxHealthAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_MaxStamina, GetMaxStaminaAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_MaxMana, GetMaxManaAttribute);

}

void USCAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(USCAttributeSet, HealthRegeneration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USCAttributeSet, ManaRegeneration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USCAttributeSet, StaminaRegeneration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USCAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USCAttributeSet, MaxStamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USCAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(USCAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USCAttributeSet, Stamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USCAttributeSet, Mana, COND_None, REPNOTIFY_Always);
}

void USCAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0, GetMaxHealth());
	}
	if (Attribute == GetStaminaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0, GetMaxStamina());
	}
	if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0, GetMaxMana());
	}
}

void USCAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const
{
	// Source : Causer of the Effect, Target : Target of the effect ; (Owner is this AS)

	Props.EffectContextHandle = Data.EffectSpec.GetContext();
	Props.SourceASC = Props.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();

	if (IsValid(Props.SourceASC) && Props.SourceASC->AbilityActorInfo.IsValid() && Props.SourceASC->AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.SourceAvatarActor = Props.SourceASC->AbilityActorInfo->AvatarActor.Get();
		Props.SourceController = Props.SourceASC->AbilityActorInfo->PlayerController.Get();
		if (Props.SourceController == nullptr && Props.SourceAvatarActor != nullptr)
		{
			if (const APawn* Pawn = Cast<APawn>(Props.SourceAvatarActor))
			{
				Props.SourceController = Pawn->GetController();
			}
		}
		if (Props.SourceController)
		{
			Props.SourceCharacter = Cast<ACharacter>(Props.SourceController->GetPawn());
		}
	}
	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		Props.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		Props.TargetCharacter = Cast<ACharacter>(Props.TargetAvatarActor);
		Props.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Props.TargetAvatarActor);
	}
}

void USCAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FEffectProperties Props;
	SetEffectProperties(Data, Props);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0, GetMaxHealth()));
	}
	if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(), 0, GetMaxMana()));
	}
	if (Data.EvaluatedData.Attribute == GetStaminaAttribute())
	{
		SetStamina(FMath::Clamp(GetStamina(), 0, GetMaxStamina()));
	}

	if (Data.EvaluatedData.Attribute == GetIncomingDamageAttribute())
	{
		const float LocalIncomingDamage = GetIncomingDamage();
		SetIncomingDamage(0.f);
		if (LocalIncomingDamage > 0.f)
		{
			const float NewHealth = GetHealth() - LocalIncomingDamage;
			SetHealth(FMath::Clamp(NewHealth, 0, GetMaxHealth()));
			const bool IsDead = NewHealth <= 0.f;

			ISCCombatInterface* CombatInterface = Cast<ISCCombatInterface>(Props.TargetAvatarActor);
			if (IsDead)
			{
				if (CombatInterface || !CombatInterface->bIsDead)
				{
					//Props.TargetASC->AddLooseGameplayTag(FSCGameplayTags::Get().Shared_State_Dead);
					CombatInterface->Die(Props.SourceAvatarActor);
					FGameplayTagContainer TagContainer;
					TagContainer.AddTag(FSCGameplayTags::Get().Shared_State_Dead);
					Props.TargetASC->TryActivateAbilitiesByTag(TagContainer);
					
				}

			}
			else
			{
				if (CombatInterface || !CombatInterface->bIsDead)
				{
					CombatInterface->OnHit(Props.SourceAvatarActor);
					//Debug::Print(Props.TargetAvatarActor->GetName() + " " + FString::SanitizeFloat(GetHealth()));
					
				}
				FGameplayTagContainer TagContainer;
				TagContainer.AddTag(FSCGameplayTags::Get().Effects_HitReact);
				Props.TargetASC->TryActivateAbilitiesByTag(TagContainer);
				
			}


		}

	}
}



void USCAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USCAttributeSet, Health, OldHealth);
}

void USCAttributeSet::OnRep_Stamina(const FGameplayAttributeData& OldStamina) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USCAttributeSet, Stamina, OldStamina);

}

void USCAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USCAttributeSet, Mana, OldMana);
}


void USCAttributeSet::OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USCAttributeSet, HealthRegeneration, OldHealthRegeneration);
}

void USCAttributeSet::OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USCAttributeSet, ManaRegeneration, OldManaRegeneration);
}

void USCAttributeSet::OnRep_StaminaRegeneration(const FGameplayAttributeData& OldStaminaRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USCAttributeSet, StaminaRegeneration, OldStaminaRegeneration);

}

void USCAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USCAttributeSet, MaxHealth, OldMaxHealth);
}

void USCAttributeSet::OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USCAttributeSet, MaxStamina, OldMaxStamina);
}

void USCAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USCAttributeSet, MaxMana, OldMaxMana);
}
