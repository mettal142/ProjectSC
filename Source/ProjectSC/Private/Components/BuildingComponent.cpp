// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/BuildingComponent.h"
#include "DataAssets/Items/BuildableItemInfo.h"
#include "Actor/BuildPreviewActor.h"
#include "Components/BoxComponent.h"
#include "Characters/SCPlayerCharacter.h"
#include "Items/Buildables/BuildableItemBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "SCDebugHelper.h"
#include "Net/UnrealNetwork.h"
#include "Engine/DataTable.h"


UBuildingComponent::UBuildingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickInterval = 0.05f;
	SetIsReplicatedByDefault(true);
}

void UBuildingComponent::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<ASCPlayerCharacter>(GetOwner());

}

void UBuildingComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UBuildingComponent, BuildableItemInfo);
	DOREPLIFETIME(UBuildingComponent, BuildTransform);
	DOREPLIFETIME(UBuildingComponent, BoxLocation);
	DOREPLIFETIME(UBuildingComponent, BoxExtent);
	DOREPLIFETIME(UBuildingComponent, bCanPlace);

}



void UBuildingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsBuildModeEnabled)
	{
		PlacePreviewMesh();
	}

}

void UBuildingComponent::LaunchBuildMode(UBuildableItemInfo* InBuildableItemInfo)
{
	check(InBuildableItemInfo);
	BuildableItemInfo = InBuildableItemInfo;
	if (bIsBuildModeEnabled)
	{
		StopBuildLoop();
		return;
	}
	if (StaticMesh = BuildableItemInfo->PreviewMesh.LoadSynchronous())
	{
		bIsBuildModeEnabled = true;
		BoxLocation = BuildableItemInfo->BoxLocation;
		BoxExtent = BuildableItemInfo->BoxExtent;
	}
}

void UBuildingComponent::RotatePreviewMesh()
{
	if (!bIsBuildModeEnabled || !BuildPreview) return;
	FRotator R = BuildTransform.GetRotation().Rotator();
	R.Yaw = FMath::UnwindDegrees(R.Yaw + 90.f);
	BuildTransform.SetRotation(R.Quaternion());
	BuildPreview->SetActorRotation(BuildTransform.Rotator());
}

void UBuildingComponent::SwitchPreviewMesh(UBuildableItemInfo* InBuildableItemInfo)
{
	if (!bIsBuildModeEnabled) return;
	check(InBuildableItemInfo);
	BuildableItemInfo = InBuildableItemInfo;
	StaticMesh = nullptr;
	if (StaticMesh = BuildableItemInfo->PreviewMesh.LoadSynchronous())
	{
		BoxLocation = BuildableItemInfo->BoxLocation;
		BoxExtent = BuildableItemInfo->BoxExtent;
		BuildPreview->StaticMesh->SetStaticMesh(StaticMesh);
		BuildPreview->OverlapBox->SetRelativeLocation(BoxLocation);
		BuildPreview->OverlapBox->SetBoxExtent(BoxExtent);
	}
}

void UBuildingComponent::PlaceStructure_Implementation(TSubclassOf<ABuildableItemBase> InBuildbleClass,const FTransform& InBuildTransform, const FVector& InBoxLocation, const FVector& InBoxExtent, bool CanPlace)
{
	if (!CanPlace || !InBuildbleClass) return;

	ABuildableItemBase* SpawndBuildable = GetWorld()->SpawnActor<ABuildableItemBase>(InBuildbleClass, InBuildTransform, FActorSpawnParameters());
	SpawndBuildable->BoxOverlap->SetRelativeLocation(InBoxLocation);
	SpawndBuildable->BoxOverlap->SetBoxExtent(InBoxExtent);
	
	
}

void UBuildingComponent::PlacePreviewMesh_Implementation()
{

	if (!IsValid(BuildPreview))
	{
		SpawnBuildPreview();
	}

	FVector CameraLocation;
	FVector CameraForwardVector;
	
	FRotator CameraRotation;

	Player->GetCameraLocation(CameraLocation);
	Player->GetCameraForwardVector(CameraForwardVector);
	//Player->GetCameraRotation(CameraRotation);

	FHitResult HitResult;

	FCollisionQueryParams CQP;
	CQP.AddIgnoredActor(GetOwner());
	CQP.AddIgnoredActor(BuildPreview);


	bool bHit = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		CameraLocation + CameraForwardVector * BuildDistanceClose,
		CameraLocation + CameraForwardVector * BuildDistanceFar,
		ECollisionChannel::ECC_Visibility,
		CQP

	);
	FVector NewLocation = bHit? HitResult.Location : HitResult.TraceEnd;

	FVector SnappedLocation;
	SnapVector(NewLocation, SnappedLocation, Snap);

	if (ExceedsStepOnAnyAxis(SnappedLocation, PrePosition, Snap))
	{
		if (bSnapMode && HitResult.GetActor() && HitResult.GetActor()->IsA(ABuildableItemBase::StaticClass()))
		{			
			SnapLocation(Cast<ABuildableItemBase>(HitResult.GetActor()), SnappedLocation);
		}

		BuildTransform.SetLocation(SnappedLocation);
		BuildPreview->SetActorTransform(BuildTransform);
		PrePosition = SnappedLocation;
	}


	bCanPlace = CheckForOverlap();

	SetPreviewColor();

}

void UBuildingComponent::SpawnBuildPreview()
{
	BuildPreview = GetWorld()->SpawnActor<ABuildPreviewActor>(ABuildPreviewActor::StaticClass(), BuildTransform, FActorSpawnParameters());

	BuildPreview->StaticMesh->SetStaticMesh(StaticMesh);
	BuildPreview->OverlapBox->SetRelativeLocation(BoxLocation);
	BuildPreview->OverlapBox->SetBoxExtent(BoxExtent);
	PrePosition = BuildTransform.GetLocation();


}

void UBuildingComponent::SnapLocation(ABuildableItemBase* HitActor, FVector& TargetLocation)
{
	TArray<FName> SocketNames = HitActor->ActorMesh->GetAllSocketNames();
	float MinValue = TNumericLimits<float>::Max();
	int MinIndex = -1;
	for (int i=0; i<SocketNames.Num(); i++)
	{
		if (SocketNames[i].ToString().Contains(BuildableItemInfo->BuildableTypeString[BuildableItemInfo->BuildableType]))
		{
			float SocketDist = FVector::Dist(TargetLocation, HitActor->ActorMesh->GetSocketLocation(SocketNames[i]));
			if (SocketDist < MinValue)
			{
				MinValue = SocketDist;
				MinIndex = i;
			}
		}
	}
	if (MinIndex >= 0)
	{
		//BuildTransform.SetLocation(HitActor->ItemMesh->GetSocketLocation(SocketNames[MinIndex]));
		TargetLocation = HitActor->ActorMesh->GetSocketLocation(SocketNames[MinIndex]);
	}


}

bool UBuildingComponent::CheckForOverlap()
{
	check(BuildPreview);

	FHitResult Hit;
	
	TArray<AActor*> ActorsToIgnore;

	ActorsToIgnore.Add(BuildPreview);

	bool bHit = UKismetSystemLibrary::BoxTraceSingle(
		this,
		BuildPreview->OverlapBox->Bounds.Origin,
		BuildPreview->OverlapBox->Bounds.Origin,
		BoxExtent,
		FRotator(0,BuildPreview->GetRootComponent()->GetComponentRotation().Yaw,0),
		UEngineTypes::ConvertToTraceType(ECC_Visibility),
		false,
		ActorsToIgnore,
		EDrawDebugTrace::None,
		Hit,
		false
		);

	return !bHit;
	
}

void UBuildingComponent::SetPreviewColor()
{
	if (!BuildPreview || !RedMaterial || !BlueMaterial) return;

	bCanPlace ? BuildPreview->StaticMesh->SetMaterial(0, BlueMaterial) : BuildPreview->StaticMesh->SetMaterial(0, RedMaterial);

}

bool UBuildingComponent::ExceedsStepOnAnyAxis(const FVector& A, const FVector& B, float Step)
{
	return (FMath::Abs(A.X - B.X) >= Step || FMath::Abs(A.Y - B.Y) >= Step || FMath::Abs(A.Z - B.Z) >= Step);
}

void UBuildingComponent::SnapVector(const FVector& V, FVector& Ret, float Grid)
{
	if (Grid <= 0.f)
	{
		Ret = V;
		return;
	}
	Ret = FVector(FMath::GridSnap(V.X, Grid), FMath::GridSnap(V.Y, Grid), FMath::GridSnap(V.Z, Grid));
	return;

}


void UBuildingComponent::StopBuildLoop()
{
	bIsBuildModeEnabled = false;

	if (IsValid(BuildPreview))
	{
		BuildPreview->Destroy();
		BuildPreview = nullptr;
		BuildableItemInfo = nullptr;
		StaticMesh = nullptr;
		bCanPlace = false;

	}
}


bool UBuildingComponent::GetCurrentBuildableItem(FBuildablesTableStructure& OutBuildableItem)
{
	check(BuildableTable);
	FName RowName = *FString::FromInt(BuildableIndex);

	if (FBuildablesTableStructure* FoundDropItem = BuildableTable->FindRow<FBuildablesTableStructure>(RowName, ""))
	{
		OutBuildableItem = *FoundDropItem;
		return true;
	}

	return false;
}
