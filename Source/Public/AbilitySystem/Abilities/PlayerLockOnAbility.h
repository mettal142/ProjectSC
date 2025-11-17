// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/SCPlayerGameplayAbility.h"
#include "PlayerLockOnAbility.generated.h"

class USCUserWidget;
class UInputMappingContext;
/**
 * 
 */
UCLASS()
class PROJECTSC_API UPlayerLockOnAbility : public USCPlayerGameplayAbility
{
	GENERATED_BODY()
protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	UFUNCTION(BlueprintCallable)
	void OnTargetLockTick(float DeltaTime);
	UFUNCTION(BlueprintCallable)
	void SwitchTarget(const FGameplayTag& InSwitchDirectionTag);

private:
	void TryLockOnTarget();
	void GetAvailableActorsToLock();
	AActor* GetNearestTargetFromAvailableActors(const TArray<AActor*>& InAvailableActors);
	void GetAvailableActorsAroundTarget(TArray<AActor*>& OutActorsOnLeft, TArray<AActor*>& OutActorsOnRight);

	void DrawTargetLockWidget();
	void SetTargetLockWidgetPosition();
	void InitTargetLockMovement();
	void InitTargetLockMappingContext();

	void CancelTargetLockAbility();
	void CleanUp();
	void ResetTargetLockMovement();
	void ResetTargetLockMappingContext();

	UPROPERTY(EditDefaultsOnly, Category = "LockOn")
	float BoxTraceDistance = 5000.f;
	UPROPERTY(EditDefaultsOnly, Category = "LockOn")
	FVector TraceBoxSize = FVector(5000.f, 5000.f, 300.f);
	UPROPERTY(EditDefaultsOnly, Category = "LockOn")
	TArray<TEnumAsByte<EObjectTypeQuery>> BoxTraceChannel;
	UPROPERTY(EditDefaultsOnly, Category = "LockOn")
	bool bShowPersistanceDebugShape = false;
	UPROPERTY(EditDefaultsOnly, Category = "LockOn")
	float CachedDefaultMaxWalkSpeed = 0.f;

	UPROPERTY(EditDefaultsOnly, Category = "LockOn")
	float TargetLockRotationInterpSpeed = 5.f;
	UPROPERTY(EditDefaultsOnly, Category = "LockOn")
	float TargetLockMaxWalkSpeed = 150.f;
	UPROPERTY(EditDefaultsOnly, Category = "LockOn")
	UInputMappingContext* TargetLockMappingContext;
	UPROPERTY(EditDefaultsOnly, Category = "LockOn")
	float TargetLockCameraOffsetDistance = 20.f;

	UPROPERTY()
	TArray <TObjectPtr<AActor>> AvailableActorsToLock;
	UPROPERTY()
	TObjectPtr<AActor> CurrentLockedActor;

	UPROPERTY()
	TObjectPtr<USCUserWidget> DrawnTargetLockWidget;
	UPROPERTY()
	FVector2D TargetLockWidgetSize = FVector2D::ZeroVector;

};
