// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Interfaces/SCCombatInterface.h"
#include "SCGameplayTags.h"
#include "SCCharacterBase.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;
class UGameplayEffect;
class UGameplayAbility;
class UNiagaraSystem;
class UCharacterCustomize;
class UStartupDataBase;
class UMotionWarpingComponent;

UCLASS()
class PROJECTSC_API ASCCharacterBase : public ACharacter, public IAbilitySystemInterface, public ISCCombatInterface
{
	GENERATED_BODY()

public:
	ASCCharacterBase();
	UFUNCTION(BlueprintCallable)
	virtual UPawnCombatComponentBase* GetPawnCombatComponent() const override;
	inline UCharacterCustomize* GetCharacterCustomizeData() { return CharacterCustomize; }
	inline TSoftObjectPtr<UStartupDataBase> GetCharacterStartupData() { return CharacterStartupData; }

	UFUNCTION(BlueprintCallable)
	void AcceptClientMovement(bool Value);

#pragma region Interfaces
	//Ability System Interface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	//Combat Interface
	virtual bool IsDead_Implementation() const override;
	virtual AActor* GetAvatar_Implementation() override;
	virtual void OnHit(AActor* CausedActor) override;
	virtual void Die(AActor* CausedActor) override;
	
	virtual UAnimMontage* GetHitReactMontage_Implementation() override;
	virtual UAnimMontage* GetDeadMontage_Implementation() override;

#pragma endregion

#pragma region Get/Set
	inline UAttributeSet* GetAttributeSet() const { return AttributeSet; }
	USkeletalMeshComponent* GetMeshByTag(FGameplayTag EquippedSocket);
#pragma endregion

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Customize")
	TObjectPtr<UCharacterCustomize> CharacterCustomize;

	UFUNCTION(NetMulticast, Reliable)
	virtual void MulticastHandleDeath();

protected:
	virtual void PossessedBy(AController* NewController) override;
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo();
	void AddCharacterEffects();
	void AddCharacterAbilities();
	virtual void InitializeMeshes();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Customize")
	TMap<FGameplayTag, TObjectPtr<USkeletalMeshComponent>> CharacterMeshMap;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	TSoftObjectPtr<UStartupDataBase> CharacterStartupData;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UMotionWarpingComponent> MotionWarpingComponent;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	USoundBase* DeathSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	FGameplayTag CharacterTag;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<UAnimMontage> HitReactMontage;
	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<UAnimMontage> DeadMontage;



};
