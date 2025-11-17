// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameplayTagContainer.h"
#include "SCCombatInterface.generated.h"

class UPawnCombatComponentBase;

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType)
class USCCombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECTSC_API ISCCombatInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual UPawnCombatComponentBase* GetPawnCombatComponent() const;
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void UpdateWarpingLocation(const FVector& TargetVector, FName WarpName);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void UpdateWarpingRotation(const FRotator& TargetRotator, FName WarpName);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FVector GetCombatSocketLocation(FName SocketName);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	AActor* GetAvatar();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool IsDead() const;

	virtual void OnHit(AActor* CausedActor);
	virtual void Die(AActor* CausedActor);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ExecuteHitEffect(const FVector& HitLocation);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Dissolve();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UAnimMontage* GetHitReactMontage();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UAnimMontage* GetDeadMontage();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UAnimMontage* GetParriedMontage();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	TArray<TSoftObjectPtr<UAnimMontage>> GetLightAttackMontages();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	TArray<TSoftObjectPtr<UAnimMontage>> GetHeavyAttackMontages();


	bool bIsDead = false;


};
