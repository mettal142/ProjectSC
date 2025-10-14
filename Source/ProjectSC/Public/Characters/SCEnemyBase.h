// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/SCCharacterBase.h"
#include "Interfaces/SCEnemyInterface.h"
#include "SCEnemyBase.generated.h"

class UWidgetComponent;
class UBehaviorTree;
class ASCAIController;

/**
 * 
 */
UCLASS()
class PROJECTSC_API ASCEnemyBase : public ASCCharacterBase, public ISCEnemyInterface
{
	GENERATED_BODY()

public:
	ASCEnemyBase();
	virtual void PossessedBy(AController* NewController) override;

#pragma region Interface
	//Combat Interface
	virtual UPawnCombatComponentBase* GetPawnCombatComponent() const override;

	virtual void OnHit(AActor* CausedActor) override;
	virtual void Die(AActor* CausedActor) override;
	TArray<UAnimMontage*> GetAttackMontages_Implementation() override;
	virtual FVector GetCombatSocketLocation_Implementation(FName SocketName) override;


	//Enemy Interface
	virtual void SetCombatTarget_Implementation(AActor* InCombatTarget) override;
	virtual AActor* GetCombatTarget_Implementation() const override;
#pragma endregion

	//UPROPERTY(BlueprintAssignable)
	//FOnAttributeChangedSignature OnHealthChanged;

	//UPROPERTY(BlueprintAssignable)
	//FOnAttributeChangedSignature OnMaxHealthChanged;

	void HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount);

	UPROPERTY(BlueprintReadOnly, Category = "Combat")
	bool bHitReacting = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	float BaseWalkSpeed = 250.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	float LifeSpan = 5.f;

	UPROPERTY(BlueprintReadWrite, Category = "Combat")
	TObjectPtr<AActor> CombatTarget;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY()
	TObjectPtr<ASCAIController> SCAIController;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UPawnCombatComponentBase> EnemyCombatComponent;


};
