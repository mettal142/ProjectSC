// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnExtensionComponentBase.h"
#include "GameplayTagContainer.h"
#include "SCTypes/SCStructTypes.h"
#include "Net/Serialization/FastArraySerializer.h"

#include "PawnCombatComponentBase.generated.h"

class ASCCharacterBase;
class ASCWeaponBase;
class UWeaponItemInfo;
class USCAnimInstanceBase;
class UArmorItemInfo;
struct FSCItemStructure;

UENUM(BlueprintType)
enum class EToggleDamageType : uint8
{
	CurrentEquippedWeapon,
	LeftHand,
	RightHand
};
/**
 * 
 */


USTRUCT(BlueprintType)
struct FEquippedWeaponEntry : public FFastArraySerializerItem
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FGameplayTag EquipSocket;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<ASCWeaponBase> Weapon = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWeaponItemInfo> WeaponInfo;
};

USTRUCT(BlueprintType)
struct FEquippedWeaponArray : public FFastArraySerializer
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FEquippedWeaponEntry> Items;

	// FastArraySerializer 필수
	bool NetDeltaSerialize(FNetDeltaSerializeInfo& DeltaParams);
};


USTRUCT(BlueprintType)
struct FEquippedArmorEntry : public FFastArraySerializerItem
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FGameplayTag EquipSocket;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<USkeletalMesh> ArmorMesh;
};

USTRUCT(BlueprintType)
struct FEquippedArmorArray : public FFastArraySerializer
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FEquippedArmorEntry> Items;

	// FastArraySerializer 필수
	bool NetDeltaSerialize(FNetDeltaSerializeInfo& DeltaParams);
};


template<>
struct TStructOpsTypeTraits<FEquippedWeaponArray> : public TStructOpsTypeTraitsBase2<FEquippedWeaponArray>
{
	enum { WithNetDeltaSerializer = true };
};

UCLASS()
class PROJECTSC_API UPawnCombatComponentBase : public UPawnExtensionComponentBase
{
	GENERATED_BODY()

public:
	UPawnCombatComponentBase();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable, Category = "SC|Combat|Items")
	void Server_EquipArmor(UArmorItemInfo* ArmorInfo);

	UFUNCTION(BlueprintCallable, Category = "SC|Combat|Items")
	ASCWeaponBase* GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const;

	UFUNCTION(BlueprintCallable, Category = "SC|Combat|Items")
	ASCWeaponBase* GetCharacterCurrentEquippedWeapon() const;

	UFUNCTION(BlueprintCallable, Category = "SC|Combat|Items")
	void RegisterSpawnedWeapon(ASCWeaponBase* InWeaponToRegister, FGameplayTag WeaponTag, bool bRegisterAsEquippedWeapon = false);

	UFUNCTION(BlueprintCallable, Category = "SC|Combat")
	void ToggleWeaponCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType = EToggleDamageType::CurrentEquippedWeapon);

	UFUNCTION(BlueprintCallable, Server, Reliable)
	void SpawnAndEquipWeapon(UWeaponItemInfo* WeaponInfo, const FGuid Guid);

	UFUNCTION(BlueprintCallable, Server, Reliable)
	void UnequipAndDestroyWeapon();
	

	UPROPERTY(Replicated, BlueprintReadWrite, Category = "SC|Combat|Items")
	FGameplayTag CurrentEquippedWeaponTag;

	UPROPERTY(BlueprintReadWrite)
	bool IsAttacking = false;

protected:
	UFUNCTION(BlueprintCallable, Category = "SC|Combat|Items")
	void EquipArmor(UArmorItemInfo* ArmorInfo);

	UFUNCTION()
	void OnRep_EquippedArmors();

	TArray<AActor*> OverlappedActors;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = "SC|Combat|Items")
	FEquippedWeaponArray EquippedWeapons;

	UPROPERTY(ReplicatedUsing = OnRep_EquippedArmors, VisibleAnywhere, BlueprintReadOnly, Category = "SC|Combat|Items")
	FEquippedArmorArray EquippedArmors;

;
	UFUNCTION(Server,Reliable)
	void ServerSetCurrentEquippedWeaponTag(FGameplayTag NewTag);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastSetWeaponAnimLayer(TSubclassOf<USCAnimInstanceBase> AnimLayer);

	
	UFUNCTION()
	void MeleeAttackTrace();

	TObjectPtr<ASCCharacterBase> OwnerCharacter;
private:
	void CheckOwnerCharacter();


	FTimerHandle WeaponTraceTimer;
	FVector PrevBoxLocation;
};

