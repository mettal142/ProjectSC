// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Field/FieldSystemActor.h"
#include "DestructionForceActor.generated.h"

class USphereComponent;

UCLASS()
class PROJECTSC_API ADestructionForceActor : public AFieldSystemActor
{
	GENERATED_BODY()
	
public:	
	ADestructionForceActor();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Radius = 500.f; 
};
