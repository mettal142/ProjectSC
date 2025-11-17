// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Equipments/SCEquippableBase.h"
#include "SCPlayerArmorBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTSC_API ASCPlayerArmorBase : public ASCEquippableBase
{
	GENERATED_BODY()
	
public:
	ASCPlayerArmorBase();

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "Equipments|Armor")
	TObjectPtr<USkeletalMeshComponent> ArmorMesh;

};
