// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/PlayerLockOnAbility.h"
#include "Characters/SCPlayerCharacter.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Blueprint/WidgetTree.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/SCPlayerController.h"
#include "SCFunctionLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "SCGameplayTags.h"
#include "Components/SizeBox.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "UI/Widgets/SCUserWidget.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

#include "AbilitySystem/SCAbilitySystemComponent.h"

#include "SCDebugHelper.h"

void UPlayerLockOnAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	TryLockOnTarget();
	InitTargetLockMappingContext();

	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UPlayerLockOnAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	ResetTargetLockMappingContext();
	CleanUp();

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UPlayerLockOnAbility::OnTargetLockTick(float DeltaTime)
{
	if (!CurrentLockedActor ||
		USCFunctionLibrary::DoesActorHaveTag(CurrentLockedActor, FSCGameplayTags::Get().Shared_State_Dead) ||
		USCFunctionLibrary::DoesActorHaveTag(GetPlayerCharacterFromActorInfo(), FSCGameplayTags::Get().Shared_State_Dead))
	{
		CancelTargetLockAbility();
		return;
	}

	SetTargetLockWidgetPosition();

	const bool bShouldOverrideRotation = !USCFunctionLibrary::DoesActorHaveTag(GetPlayerCharacterFromActorInfo(), FSCGameplayTags::Get().Player_State_Evade);

	FRotator LookAtRot = UKismetMathLibrary::FindLookAtRotation(GetPlayerCharacterFromActorInfo()->GetActorLocation(), CurrentLockedActor->GetActorLocation());
	LookAtRot -= FRotator(TargetLockCameraOffsetDistance, 0.f, 0.f);

	const FRotator CurrentControlRot = GetPlayerControllerFromActorInfo()->GetControlRotation();
	const FRotator TargetRot = FMath::RInterpTo(CurrentControlRot, LookAtRot, DeltaTime, TargetLockRotationInterpSpeed);

	GetPlayerControllerFromActorInfo()->SetControlRotation(FRotator(TargetRot.Pitch, TargetRot.Yaw, 0.f));

	if (bShouldOverrideRotation)
	{
		GetPlayerCharacterFromActorInfo()->SetActorRotation(FRotator(0.f, TargetRot.Yaw, 0.f));

	}

}

void UPlayerLockOnAbility::SwitchTarget(const FGameplayTag& InSwitchDirectionTag)
{
	GetAvailableActorsToLock();

	TArray<AActor*> ActorsOnLeft;
	TArray<AActor*> ActorsOnRight;
	AActor* NewTargetToLock = nullptr;

	GetAvailableActorsAroundTarget(ActorsOnLeft, ActorsOnRight);

	if (InSwitchDirectionTag == FSCGameplayTags::Get().Event_SwitchTarget_Left)
	{
		NewTargetToLock = GetNearestTargetFromAvailableActors(ActorsOnLeft);

	}
	else
	{
		NewTargetToLock = GetNearestTargetFromAvailableActors(ActorsOnRight);

	}
	if (NewTargetToLock)
	{
		CurrentLockedActor = NewTargetToLock;
	}


}

void UPlayerLockOnAbility::TryLockOnTarget()
{
	GetAvailableActorsToLock();

	if (AvailableActorsToLock.IsEmpty())
	{
		CancelTargetLockAbility();
		return;
	}

	CurrentLockedActor = GetNearestTargetFromAvailableActors(AvailableActorsToLock);

	if (CurrentLockedActor)
	{
		DrawTargetLockWidget();
		SetTargetLockWidgetPosition();
	}
	else
	{
		CancelTargetLockAbility();
	}
	
}

void UPlayerLockOnAbility::GetAvailableActorsToLock()
{
	AvailableActorsToLock.Empty();
	TArray<FHitResult> Hits;

	UKismetSystemLibrary::BoxTraceMultiForObjects(
		GetPlayerCharacterFromActorInfo(),
		GetPlayerCharacterFromActorInfo()->GetActorLocation(),
		GetPlayerCharacterFromActorInfo()->GetActorLocation() + GetPlayerCharacterFromActorInfo()->GetActorForwardVector() * BoxTraceDistance,
		TraceBoxSize / 2,
		GetPlayerCharacterFromActorInfo()->GetActorForwardVector().ToOrientationRotator(),
		BoxTraceChannel,
		false,
		TArray<AActor*>(),
		bShowPersistanceDebugShape ? EDrawDebugTrace::Persistent : EDrawDebugTrace::None,
		Hits,
		true
	);

	for (const FHitResult& Hit : Hits)
	{
		if (AActor* HitActor = Hit.GetActor())
		{
			if (HitActor != GetPlayerCharacterFromActorInfo() && !HitActor->IsA(ASCPlayerCharacter::StaticClass()))
			{
				AvailableActorsToLock.AddUnique(HitActor);
			}
		}
	}

}

AActor* UPlayerLockOnAbility::GetNearestTargetFromAvailableActors(const TArray<AActor*>& InAvailableActors)
{
	float ClosetDistance = 0.f;
	return UGameplayStatics::FindNearestActor(GetPlayerCharacterFromActorInfo()->GetActorLocation(), InAvailableActors, ClosetDistance);
}

void UPlayerLockOnAbility::GetAvailableActorsAroundTarget(TArray<AActor*>& OutActorsOnLeft, TArray<AActor*>& OutActorsOnRight)
{
	if (!CurrentLockedActor || AvailableActorsToLock.IsEmpty())
	{
		CancelTargetLockAbility();
		return;
	}

	const FVector PlayerLocation = GetPlayerCharacterFromActorInfo()->GetActorLocation();
	const FVector PlayerToCurrentNormalized = (CurrentLockedActor->GetActorLocation() - PlayerLocation).GetSafeNormal();

	for (AActor* AvailableActor : AvailableActorsToLock)
	{
		if (!AvailableActor || AvailableActor == CurrentLockedActor) continue;
		
		const FVector PlayerToAvailableNormalized = (AvailableActor->GetActorLocation() - PlayerLocation).GetSafeNormal();
		const FVector CrossResult = FVector::CrossProduct(PlayerToCurrentNormalized, PlayerToAvailableNormalized);
		if (CrossResult.Z > 0.f)
		{
			OutActorsOnRight.AddUnique(AvailableActor);
		}
		else
		{
			OutActorsOnLeft.AddUnique(AvailableActor);
		}
	}
}

void UPlayerLockOnAbility::DrawTargetLockWidget()
{
	if (!DrawnTargetLockWidget)
	{		
		DrawnTargetLockWidget = CreateWidget<USCUserWidget>(GetPlayerControllerFromActorInfo(), GetPlayerCharacterFromActorInfo()->TargetLockWidgetClass);
		check(DrawnTargetLockWidget);
		DrawnTargetLockWidget->AddToViewport();
	}
}

void UPlayerLockOnAbility::SetTargetLockWidgetPosition()
{
	if (!DrawnTargetLockWidget || !CurrentLockedActor)
	{
		CancelTargetLockAbility();
		return;
	}

	FVector2D ScreenPosition;
	UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition(
		GetPlayerControllerFromActorInfo(),
		CurrentLockedActor->GetActorLocation(),
		ScreenPosition,
		true
	);

	DrawnTargetLockWidget->WidgetTree->ForEachWidget(
		[this](UWidget* FoundWidget)
	{
		if (USizeBox* FoundSizeBox = Cast<USizeBox>(FoundWidget))
		{
			TargetLockWidgetSize.X = FoundSizeBox->GetWidthOverride();
			TargetLockWidgetSize.Y = FoundSizeBox->GetHeightOverride();
		}
	}
	);

	ScreenPosition -= (TargetLockWidgetSize / 2.f);

	DrawnTargetLockWidget->SetPositionInViewport(ScreenPosition, false);
}


void UPlayerLockOnAbility::InitTargetLockMappingContext()
{

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetPlayerControllerFromActorInfo()->GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(TargetLockMappingContext, 3);
	}

}

void UPlayerLockOnAbility::CancelTargetLockAbility()
{
	CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true);

}

void UPlayerLockOnAbility::CleanUp()
{
	AvailableActorsToLock.Empty();
	CurrentLockedActor = nullptr;
	if (DrawnTargetLockWidget)
	{
		DrawnTargetLockWidget->RemoveFromParent();
	}
	DrawnTargetLockWidget = nullptr;
	TargetLockWidgetSize = FVector2D::ZeroVector;
	CachedDefaultMaxWalkSpeed = 0.f;
}


void UPlayerLockOnAbility::ResetTargetLockMappingContext()
{
	if (!GetPlayerControllerFromActorInfo())
	{
		return;
	}
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetPlayerControllerFromActorInfo()->GetLocalPlayer()))
	{
		Subsystem->RemoveMappingContext(TargetLockMappingContext);
	}
}
