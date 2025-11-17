// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SCPlayerState.h"
#include "AbilitySystem/SCAbilitySystemComponent.h"
#include "AbilitySystem/SCAttributeSet.h"
#include "Net/UnrealNetwork.h"

ASCPlayerState::ASCPlayerState()
{
	NetUpdateFrequency = 100.f;
	AbilitySystemComponent = CreateDefaultSubobject<USCAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<USCAttributeSet>("AttributeSet");
}

void ASCPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ASCPlayerState, Level);
}

UAbilitySystemComponent* ASCPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ASCPlayerState::OnRep_Level(int32 OldLevel)
{
}
