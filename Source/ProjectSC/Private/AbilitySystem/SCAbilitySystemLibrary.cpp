// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/SCAbilitySystemLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "UI/WidgetController/SCWidgetController.h"
#include "UI/HUD/SCHUD.h"
#include "Player/SCPlayerState.h"
#include "AbilitySystem/SCAbilitySystemComponent.h"
#include "Interfaces/SCCombatInterface.h"
#include "Engine/OverlapResult.h"
#include "GameModes/SCGameModeBase.h"


bool USCAbilitySystemLibrary::MakeWidgetControllerParams(const UObject* WorldContextObject, FWidgetControllerParams& OutWCParams, ASCHUD*& OutSCHUD)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		OutSCHUD = Cast<ASCHUD>(PC->GetHUD());
		if (OutSCHUD)
		{
			
			ASCPlayerState* PS = PC->GetPlayerState<ASCPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			OutWCParams.PlayerState = PS;
			OutWCParams.AbilitySystemComponent = ASC;
			OutWCParams.PlayerController = PC;
			OutWCParams.AttributeSet = AS;

			return true;
		}
	}

	return false;
}

UMenuWidgetController* USCAbilitySystemLibrary::GetMenuWidgetController(const UObject* WorldContextObject)
{
	FWidgetControllerParams WCParams;
	ASCHUD* SCHUD = nullptr;

	if (MakeWidgetControllerParams(WorldContextObject, WCParams, SCHUD))
	{
		return SCHUD->GetMenuWidgetController(WCParams);
	}

	return nullptr;
}

UInGameOverlayWidgetController* USCAbilitySystemLibrary::GetInGameOverlayWidgetController(const UObject* WorldContextObject)
{
	FWidgetControllerParams WCParams;
	ASCHUD* SCHUD = nullptr;

	if (MakeWidgetControllerParams(WorldContextObject, WCParams, SCHUD))
	{
		return SCHUD->GetInGameOverlayWidgetController(WCParams);
	}

	return nullptr;
}

UQuickSlotWidgetController* USCAbilitySystemLibrary::GetQuickSlotWidgetController(const UObject* WorldContextObject)
{
	FWidgetControllerParams WCParams;
	ASCHUD* SCHUD = nullptr;

	if (MakeWidgetControllerParams(WorldContextObject, WCParams, SCHUD))
	{
		return SCHUD->GetQuickSlotWidgetController(WCParams);
	}
	return nullptr;
}

void USCAbilitySystemLibrary::GetLivePlayersWithinRadius(const UObject* WorldContextObject, TArray<AActor*>& OutOverlappingActors, const TArray<AActor*>& ActorsToIgnore, float Radius, const FVector& SphereOrigin)
{
	FCollisionQueryParams SphereParams;
	SphereParams.AddIgnoredActors(ActorsToIgnore);

	if (const UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		TArray<FOverlapResult> Overlaps;
		World->OverlapMultiByObjectType(Overlaps, SphereOrigin, FQuat::Identity, FCollisionObjectQueryParams(FCollisionObjectQueryParams::InitType::AllDynamicObjects), FCollisionShape::MakeSphere(Radius), SphereParams);

		for (FOverlapResult& Overlap : Overlaps)
		{
			if (Overlap.GetActor()->Implements<USCCombatInterface>() && !ISCCombatInterface::Execute_IsDead(Overlap.GetActor()))
			{
				OutOverlappingActors.AddUnique(ISCCombatInterface::Execute_GetAvatar(Overlap.GetActor()));
			}
		}
	}

}

void USCAbilitySystemLibrary::InitializeDefaultAttributes(const UObject* WorldContextObject, ECharacterClass CharacterClass, float Level, UAbilitySystemComponent* ASC)
{
	AActor* AvatarActor = ASC->GetAvatarActor();

	UCharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WorldContextObject);

	FCharacterClassDefaultInfo ClassDefaultInfo = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);

	FGameplayEffectContextHandle PrimaryAttributesContextHandle = ASC->MakeEffectContext();
	PrimaryAttributesContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle PrimaryAttributesSpecHandle = ASC->MakeOutgoingSpec(ClassDefaultInfo.PrimaryAttributes, Level, PrimaryAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*PrimaryAttributesSpecHandle.Data.Get());

	FGameplayEffectContextHandle SecondaryAttributesContextHandle = ASC->MakeEffectContext();
	SecondaryAttributesContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle SecondaryAttributesSpecHandle = ASC->MakeOutgoingSpec(CharacterClassInfo->SecondaryAttributes, Level, SecondaryAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*SecondaryAttributesSpecHandle.Data.Get());

	FGameplayEffectContextHandle VitalAttributesContextHandle = ASC->MakeEffectContext();
	VitalAttributesContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle VitalAttributesSpecHandle = ASC->MakeOutgoingSpec(CharacterClassInfo->VitalAttributes, Level, VitalAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*VitalAttributesSpecHandle.Data.Get());

}

void USCAbilitySystemLibrary::ApplyEffectToTargetActor(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (!TargetASC||!GameplayEffectClass) return;

	FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(TargetActor);
	const FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(GameplayEffectClass, 1, EffectContextHandle);
	TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());

}

UCharacterClassInfo* USCAbilitySystemLibrary::GetCharacterClassInfo(const UObject* WorldContextObject)
{
	ASCGameModeBase* SCGameMode = Cast<ASCGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (SCGameMode == nullptr)
		return nullptr;

	return SCGameMode->CharacterClassInfo;
}

void USCAbilitySystemLibrary::SetLooseTagCount(UAbilitySystemComponent* ASC, FGameplayTag Tag, int32 NewCount)
{
	if (!ASC) return;
	ASC->SetLooseGameplayTagCount(Tag, NewCount);
}
