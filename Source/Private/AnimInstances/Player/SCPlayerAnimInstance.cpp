// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/Player/SCPlayerAnimInstance.h"
#include "Characters/SCPlayerCharacter.h"
void USCPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (OwningCharacter)
	{
		OwningPlayerCharacter = Cast<ASCPlayerCharacter>(OwningCharacter);
	}
}

void USCPlayerAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
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
