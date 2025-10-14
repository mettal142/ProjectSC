// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuildPreviewActor.generated.h"

class UBoxComponent;

UCLASS()
class PROJECTSC_API ABuildPreviewActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ABuildPreviewActor();

	TObjectPtr<UStaticMeshComponent> StaticMesh;

	TObjectPtr<UBoxComponent> OverlapBox;

};
