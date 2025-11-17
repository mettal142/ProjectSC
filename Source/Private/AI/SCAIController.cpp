// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SCAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"

ASCAIController::ASCAIController()
{
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>("BlackboardComponent");
	check(BlackboardComponent);
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>("BehaviorTreeComponent");
	check(BehaviorTreeComponent);
}
