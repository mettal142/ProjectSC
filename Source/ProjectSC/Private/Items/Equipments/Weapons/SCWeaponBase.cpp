// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Equipments/Weapons/SCWeaponBase.h"
#include "SCFunctionLibrary.h"
#include "Components/BoxComponent.h"
#include "AnimInstances/SCAnimInstanceBase.h"
#include "Net/UnrealNetwork.h"

ASCWeaponBase::ASCWeaponBase()
{
	PrimaryActorTick.bCanEverTick = false;

	bReplicates = true;
	SetReplicateMovement(true);

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("EquipmentMesh"));
	SetRootComponent(WeaponMesh);

	WeaponCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponCollisionBox"));
	WeaponCollisionBox->SetupAttachment(GetRootComponent());
	WeaponCollisionBox->SetBoxExtent(FVector(20.f));
	WeaponCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

void ASCWeaponBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASCWeaponBase, AttackMontages);
	DOREPLIFETIME(ASCWeaponBase, WeaponGuid);
	DOREPLIFETIME(ASCWeaponBase, OwnerCharacter);

}


void ASCWeaponBase::AssignGrantedAbilitySpecHandles(const TArray<FGameplayAbilitySpecHandle>& InSpecHandles)
{
	GrantedAbilitySpecHandle = InSpecHandles;
}

TArray<FGameplayAbilitySpecHandle> ASCWeaponBase::GetGrantedAbilitySpecHandles() const
{
	return GrantedAbilitySpecHandle;
}
