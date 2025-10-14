// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SCGameplayTags.h"
#include "CharacterCustomize.generated.h"

USTRUCT(BlueprintType)
struct FCustomizableMesh
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag Tag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USkeletalMesh> Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<UMaterialInterface>> Materials;


};

/**
 * 
 */
UCLASS()
class PROJECTSC_API UCharacterCustomize : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterCustomize")
	TArray<FCustomizableMesh> CharacterMeshList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UMaterialInterface> HeadMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UMaterialInterface> BodyMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FName, TObjectPtr<UMaterialInterface>> MaterialMap;
};
