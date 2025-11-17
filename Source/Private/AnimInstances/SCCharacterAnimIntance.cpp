// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/SCCharacterAnimIntance.h"
#include "Characters/SCCharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "KismetAnimationLibrary.h"

void USCCharacterAnimIntance::NativeInitializeAnimation()
{
	OwningCharacter = Cast<ASCCharacterBase>(TryGetPawnOwner());
	if(OwningCharacter)
	{
		OwningMovementComponent = OwningCharacter->GetCharacterMovement();
	}
}

void USCCharacterAnimIntance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	if (!OwningCharacter || !OwningMovementComponent) return;

	GroundSpeed = OwningCharacter->GetVelocity().Size2D();
	bHasAcceleration = OwningMovementComponent->GetCurrentAcceleration().SizeSquared2D() > 0.f;
	LocomotionDirection = UKismetAnimationLibrary::CalculateDirection(OwningCharacter->GetVelocity(), OwningCharacter->GetActorRotation());
}
