// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnExtensionComponentBase.h"
#include "BuildingComponent.generated.h"

class UBuildableItemInfo;
class ABuildPreviewActor;
class ASCPlayerCharacter;
class ABuildableItemBase;
/**
 * 
 */
UCLASS()
class PROJECTSC_API UBuildingComponent : public UPawnExtensionComponentBase
{
	GENERATED_BODY()
	
public: 
	UBuildingComponent();
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable)
	void LaunchBuildMode(UBuildableItemInfo* InBuildableItemInfo);

	UFUNCTION(BlueprintCallable)
	void RotatePreviewMesh();

	UFUNCTION(BlueprintCallable)
	void SwitchPreviewMesh(UBuildableItemInfo* InBuildableItemInfo);

	UFUNCTION(BlueprintCallable)
	void StopBuildLoop();

	UFUNCTION(BlueprintCallable, Server, Reliable)
	void PlaceStructure(TSubclassOf<ABuildableItemBase> InBuildbleClass, const FTransform& InBuildTransform, const FVector& InBoxLocation, const FVector& InBoxExtent, bool CanPlace);

	UFUNCTION(BlueprintCallable)
	inline  UBuildableItemInfo* GetCurrentStructure() { return BuildableItemInfo; }
	
	UFUNCTION(BlueprintCallable)
	bool GetCurrentBuildableItem(FBuildablesTableStructure& OutBuildableItem);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Snap = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bSnapMode = true;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated)
	bool bCanPlace;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UMaterial> RedMaterial;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UMaterial> BlueMaterial;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated)
	FVector BoxLocation;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated)
	FVector BoxExtent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated)
	FTransform BuildTransform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int BuildableIndex = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UDataTable> BuildableTable;

private:
	UFUNCTION(Client,Reliable)
	void PlacePreviewMesh();
	
	UFUNCTION()
	void SpawnBuildPreview();

	void SnapLocation(ABuildableItemBase* HitActor, FVector& TargetLocation);

	bool CheckForOverlap();

	void SetPreviewColor();

	bool ExceedsStepOnAnyAxis(const FVector& A, const FVector& B, float Step);

	void SnapVector(const FVector& V,FVector& Ret ,float Grid);



	bool bIsBuildModeEnabled = false;
	
	TObjectPtr<ABuildPreviewActor> BuildPreview;
	
	TObjectPtr<UStaticMesh> StaticMesh;

	FVector PrePosition;

	UPROPERTY(EditDefaultsOnly)
	int BuildDistanceClose = 350;

	UPROPERTY(EditDefaultsOnly)
	int BuildDistanceFar = 1000;

	UPROPERTY()
	TObjectPtr<ASCPlayerCharacter> Player;

	UPROPERTY(Replicated)
	TObjectPtr<UBuildableItemInfo>  BuildableItemInfo;



};
