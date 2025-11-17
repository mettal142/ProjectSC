// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/SCCharacterBase.h"
#include "SCGameplayTags.h"
#include "SCPlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UPlayerCombatComponent;
class UInventoryComponent;
class UQuickSlotComponent;
class UBuildingComponent;

struct FCustomizableMesh;
/**
 * 
 */
UCLASS()
class PROJECTSC_API ASCPlayerCharacter : public ASCCharacterBase
{
	GENERATED_BODY()
public:
	ASCPlayerCharacter();
	virtual UPawnCombatComponentBase* GetPawnCombatComponent() const override;
	UInventoryComponent* GetInventoryComponent() const;
	UQuickSlotComponent* GetQuickSlotComponent() const;
	UBuildingComponent* GetBuildingComponent() const;
	UFUNCTION(BlueprintPure)
	void GetCameraLocation(FVector& Location);
	UFUNCTION(BlueprintPure)
	void GetCameraForwardVector(FVector& ForwardVector);
	UFUNCTION(BlueprintPure)
	void GetCameraRotation(FRotator& Rotation);

	virtual void OnRep_PlayerState() override;
	virtual void PossessedBy(AController* NewController) override;


protected:
	virtual void BeginPlay() override;

private:
	virtual void InitAbilityActorInfo() override;
	UFUNCTION(BlueprintCallable)
	void SetLeaderMesh();

#pragma region Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPlayerCombatComponent> PlayerCombatComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInventoryComponent> InventoryComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UQuickSlotComponent> QuickSlotComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBuildingComponent> BuildingComponent;
#pragma endregion

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FollowCamera;



};
