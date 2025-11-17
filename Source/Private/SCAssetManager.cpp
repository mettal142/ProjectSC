// Fill out your copyright notice in the Description page of Project Settings.


#include "SCAssetManager.h"
#include "SCGameplayTags.h"
#include "AbilitySystemGlobals.h"

USCAssetManager& USCAssetManager::Get()
{
	check(GEngine);

	USCAssetManager* SCAssetManager = Cast<USCAssetManager>(GEngine->AssetManager);
	return *SCAssetManager;
}

void USCAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	FSCGameplayTags::InitializeNativeGameplayTags();
	UAbilitySystemGlobals::Get().InitGlobalData();

}
