// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/DestructionForceActor.h"
#include "Components/SphereComponent.h"
#include "Field/FieldSystemComponent.h"
#include "Field/FieldSystemObjects.h"

ADestructionForceActor::ADestructionForceActor()
{
	PrimaryActorTick.bCanEverTick = false;

}

void ADestructionForceActor::BeginPlay()
{
	Super::BeginPlay();
	//URadialFalloff* RadialFallOff = NewObject<URadialFalloff>(this);
	//RadialFallOff->SetRadialFalloff(
	//	50000,
	//	0,
	//	1,
	//	0,
	//	Radius ,
	//	GetActorLocation(),
	//	Field_Falloff_Linear
	//);

	//UFieldSystemMetaDataFilter* Meta = NewObject<UFieldSystemMetaDataFilter>(this);
	//Meta->FilterType = EFieldFilterType::Field_Filter_Dynamic;
	//Meta->ObjectType = EFieldObjectType::Field_Object_Destruction;
	//

	//FieldSystemComponent->ApplyPhysicsField(true, Field_ExternalClusterStrain , Meta, RadialFallOff);

	////Destroy();
	
}
