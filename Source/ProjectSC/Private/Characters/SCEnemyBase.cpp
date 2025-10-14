// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SCEnemyBase.h"
#include "AbilitySystem/SCAbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AbilitySystem/SCAttributeSet.h"
#include "SCGameplayTags.h"
#include "AbilitySystem/Data/EnemyStartupData.h"
#include "Components/Combat/PawnCombatComponentBase.h"
#include "Items/Equipments/Weapons/SCWeaponBase.h"
#include "AI/SCAIController.h"
#include "BehaviorTree//BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"


ASCEnemyBase::ASCEnemyBase()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	AbilitySystemComponent = CreateDefaultSubobject<USCAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	AttributeSet = CreateDefaultSubobject<USCAttributeSet>("AttributeSet");
	EnemyCombatComponent = CreateDefaultSubobject<UPawnCombatComponentBase>(TEXT("EnemyCombatComponent"));


}

void ASCEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	AbilitySystemComponent->RegisterGameplayTagEvent(FSCGameplayTags::Get().Effects_HitReact, EGameplayTagEventType::NewOrRemoved).AddUObject(
		this,
		&ThisClass::HitReactTagChanged
	);
}

void ASCEnemyBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitAbilityActorInfo();
	AddCharacterEffects();
	AddCharacterAbilities();

	if (!HasAuthority()) return;

	SCAIController = Cast<ASCAIController>(NewController);
	SCAIController->GetBlackboardComponent()->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	SCAIController->RunBehaviorTree(BehaviorTree);
	SCAIController->GetBlackboardComponent()->SetValueAsBool(FName("HitReacting"), false);	

}

UPawnCombatComponentBase* ASCEnemyBase::GetPawnCombatComponent() const
{
	return EnemyCombatComponent;
}

void ASCEnemyBase::OnHit(AActor* CausedActor)
{

}

void ASCEnemyBase::Die(AActor* CausedActor)
{
	FGameplayTagContainer AbilityTags;
	AbilityTags.AddTag(FSCGameplayTags::Get().Shared_State_Dead);
	AbilitySystemComponent->TryActivateAbilitiesByTag(AbilityTags);

	SetLifeSpan(LifeSpan);
	if (SCAIController)
	{
		SCAIController->GetBlackboardComponent()->SetValueAsBool(FName("IsDead"), true);
	}
	Super::Die(CausedActor);
}

TArray<UAnimMontage*> ASCEnemyBase::GetAttackMontages_Implementation()
{
	return CharacterStartupData->AttackMontages;
}

FVector ASCEnemyBase::GetCombatSocketLocation_Implementation(FName SocketName)
{
	check(EnemyCombatComponent);
	if (ASCWeaponBase* EquippedWeapon = EnemyCombatComponent->GetCharacterCurrentEquippedWeapon())
	{
		return EquippedWeapon->GetWeaponMesh()->GetSocketLocation(SocketName);
	}
	else
	{
		GetMesh()->GetSocketLocation(SocketName);
	}

	return FVector();
}

void ASCEnemyBase::SetCombatTarget_Implementation(AActor* InCombatTarget)
{
	CombatTarget = InCombatTarget;
}

AActor* ASCEnemyBase::GetCombatTarget_Implementation() const
{
	return CombatTarget;
}

void ASCEnemyBase::HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	bHitReacting = NewCount > 0;
	GetCharacterMovement()->MaxWalkSpeed = bHitReacting ? 0.f : BaseWalkSpeed;
	if (SCAIController && SCAIController->GetBlackboardComponent())
	{
		SCAIController->GetBlackboardComponent()->SetValueAsBool(FName("HitReacting"), bHitReacting);
	}

}

