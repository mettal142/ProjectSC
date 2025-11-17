// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/Enemy/SCEnemyAnimInstance.h"
#include "Characters/SCEnemyBase.h"

void USCEnemyAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (OwningCharacter)
	{
		OwningEnemyCharacter = Cast<ASCEnemyBase>(OwningCharacter);
	}
}

void USCEnemyAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);

	if (bHasAcceleration)
	{
		IdleElpasedTime = 0.f;
		bShouldEnterRelaxState = false;
	}
	else
	{
		IdleElpasedTime += DeltaSeconds;
		bShouldEnterRelaxState = (IdleElpasedTime >= EnterRelaxStateThreshold);


	}
}
