// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AbilitySystemInterface.h"
#include "Interfaces/SCCombatInterface.h"
#include "GameplayTagContainer.h"
#include "DestructableActorBase.generated.h"

class UBoxComponent;
class UGeometryCollectionComponent;
class UGameplayEffect;
class USCAbilitySystemComponent;
class USCAttributeSet;
class USCGameInstance;
class AItemActor;
class AFieldSystemActor;
struct FDropItemStructure;

UCLASS()
class PROJECTSC_API ADestructableActorBase : public AActor, public ISCCombatInterface, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:	
	ADestructableActorBase();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

#pragma region CombatInterface 
	virtual void OnHit(AActor* CausedActor) override;
	virtual void Die(AActor* CausedActor) override;	
	virtual void ExecuteHitEffect_Implementation(const FVector& HitLocation) override;

#pragma endregion
	
	UFUNCTION(Server, Reliable)
	void ServerCreateDropItem();

	UFUNCTION(Server, Reliable)
	void ServerCreateAllDropItem();

	UFUNCTION(NetMulticast,Reliable)
	void MulticastDestruction();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> ActorMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UBoxComponent> BoxOverlap;


protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UGeometryCollectionComponent> DestMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	TObjectPtr<USCAbilitySystemComponent> ASC;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	TObjectPtr<USCAttributeSet> SCAttributeSet;
	UPROPERTY(EditDefaultsOnly, Category = "StartupData")
	TArray<TSubclassOf<UGameplayEffect>> Effects;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int DropTableID = 0;


	UPROPERTY(Replicated)
	TArray<FDropItemStructure> DropItems;

	UPROPERTY()
	USCGameInstance* GI;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AFieldSystemActor> DestForceActorClass;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag HitEffectCueTag;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag HitSoundCueTag;


};
