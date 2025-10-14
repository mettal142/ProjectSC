// Fill out your copyright notice in the Description page of Project Settings.


#include "SCGameInstance.h"

void USCGameInstance::Init()
{
	Super::Init();
	
	if (DataManagerClass)
	{
		DataManager = NewObject<USCDataManager>(this, DataManagerClass);
	}
}
