// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Equipments/SCEquippableBase.h"
#include "GameplayAbilitySpecHandle.h"
#include "SCTypes/SCStructTypes.h"

#include "SCWeaponBase.generated.h"

class UBoxComponent;
class USCAnimInstanceBase;


/**
 * 
 */
UCLASS()
class PROJECTSC_API ASCWeaponBase : public ASCEquippableBase
{
	GENERATED_BODY()

public:
	ASCWeaponBase();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	inline USkeletalMeshComponent* GetWeaponMesh() { return WeaponMesh; }

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnEquipWeapon();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnUnequipWeapon();

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Equipments|Weapon")
	TArray<TSoftObjectPtr<UAnimMontage>> AttackMontages;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly)
	FGuid WeaponGuid;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly)
	APawn* OwnerCharacter;



protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Equipments|Weapon")
	TObjectPtr<UBoxComponent> WeaponCollisionBox;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Equipments|Weapon")
	TObjectPtr<USkeletalMeshComponent> WeaponMesh;
	TArray<FGameplayAbilitySpecHandle> GrantedAbilitySpecHandle;


public:
	inline TObjectPtr<UBoxComponent> GetWeaponCollisionBox() { return WeaponCollisionBox; }

	UFUNCTION(BlueprintCallable)
	void AssignGrantedAbilitySpecHandles(const TArray<FGameplayAbilitySpecHandle>& InSpecHandles);

	UFUNCTION(BlueprintCallable)
	TArray<FGameplayAbilitySpecHandle> GetGrantedAbilitySpecHandles() const;



};
