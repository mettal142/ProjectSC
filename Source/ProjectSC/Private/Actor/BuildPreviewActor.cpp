// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/BuildPreviewActor.h"
#include "Components/BoxComponent.h"

ABuildPreviewActor::ABuildPreviewActor()
{
	PrimaryActorTick.bCanEverTick = false;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(GetRootComponent());

	OverlapBox = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapBox"));
	OverlapBox->SetupAttachment(StaticMesh);


	StaticMesh->SetCollisionResponseToAllChannels(ECR_Ignore);	
	OverlapBox->SetCollisionResponseToAllChannels(ECR_Overlap);

}

