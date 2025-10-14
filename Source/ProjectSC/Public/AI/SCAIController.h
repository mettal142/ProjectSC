// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SCAIController.generated.h"

class UBlackboardComponent;
class UBehaviorTreeComponent;
/**
 * 
 */
UCLASS()
class PROJECTSC_API ASCAIController : public AAIController
{
	GENERATED_BODY()

public:
	ASCAIController();

protected:
	UPROPERTY()
	TObjectPtr<UBlackboardComponent> BlackboardComponent;
	UPROPERTY()
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;
};
