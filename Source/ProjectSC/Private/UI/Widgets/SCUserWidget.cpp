// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/SCUserWidget.h"

void USCUserWidget::NativeConstruct()
{
	Super::NativeConstruct();	
}

void USCUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();

}
