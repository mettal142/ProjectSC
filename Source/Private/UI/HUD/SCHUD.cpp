// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/SCHUD.h"
#include "Kismet/GameplayStatics.h"
#include "Player/SCPlayerController.h"
#include "Player/SCPlayerState.h"
#include "UI/Widgets/SCMenuWidget.h"
#include "AbilitySystem/SCAbilitySystemLibrary.h"
#include "UI/Widgets/SCInGameOverlayWidget.h"
#include "UI/WidgetController/MenuWidgetController.h"
#include "UI/WidgetController/InGameOverlayWidgetController.h"
#include "UI/WidgetController/QuickSlotWidgetController.h"


void ASCHUD::BeginPlay()
{
	Super::BeginPlay();

}
void ASCHUD::InitWidgets(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	SetWidgetControllerParams(PC, PS, ASC, AS);

	GetInGameOverlayWidget();
	InGameOverlayWidget->AddToViewport();
	GetMenuWidget();
	MenuWidget->AddToViewport();
	HUDSet();
}
void ASCHUD::InitQuickSlotWidget(ASCPlayerCharacter* PlayerCharacter)
{
	GetQuickSlotWidgetController();
	QuickSlotWidgetController->SetQuickSlotComponent(PlayerCharacter);
	QuickSlotWidgetController->BindCallbacksToDependencies();
	InGameOverlayWidget->InitQuickSlot();
}
void ASCHUD::SetWidgetControllerParams(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	WidgetControllerParams.PlayerController = PC;
	WidgetControllerParams.PlayerState = PS;
	WidgetControllerParams.AbilitySystemComponent = ASC;
	WidgetControllerParams.AttributeSet = AS;
}

void ASCHUD::GetWidgetControllerParams(FWidgetControllerParams& OutWCParams)
{
	OutWCParams = WidgetControllerParams;
}

UMenuWidgetController* ASCHUD::GetMenuWidgetController(const FWidgetControllerParams& WCParams)
{
	if (!MenuWidgetController)
	{
		check(MenuWidgetControllerClass);
		MenuWidgetController = NewObject<UMenuWidgetController>(this, MenuWidgetControllerClass);
		MenuWidgetController->SetWidgetControllerParams(WCParams);
		MenuWidgetController->BindCallbacksToDependencies();
	}

	return MenuWidgetController;
}

UInGameOverlayWidgetController* ASCHUD::GetInGameOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if (!InGameOverlayWidgetController)
	{
		check(InGameOverlayWidgetControllerClass);
		InGameOverlayWidgetController = NewObject<UInGameOverlayWidgetController>(this, InGameOverlayWidgetControllerClass);
		InGameOverlayWidgetController->SetWidgetControllerParams(WCParams);
		InGameOverlayWidgetController->BindCallbacksToDependencies();

	}
	return InGameOverlayWidgetController;
}

UQuickSlotWidgetController* ASCHUD::GetQuickSlotWidgetController()
{
	if (!QuickSlotWidgetController)
	{
		check(QuickSlotWidgetControllerClass);
		QuickSlotWidgetController = NewObject<UQuickSlotWidgetController>(this, QuickSlotWidgetControllerClass);
		QuickSlotWidgetController->SetWidgetControllerParams(WidgetControllerParams);
		QuickSlotWidgetController->BindCallbacksToDependencies();
		InGameOverlayWidget->InitQuickSlot();
	}
	return QuickSlotWidgetController;
}

void ASCHUD::DisplayGameWidget(EGameState GameState, EMenuType MenuType)
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	switch (GameState)
	{
	case EGameState::Playing:

		if (bMenuWidgetOpened)
		{
			MenuWidgetController->OnSetVisibilitySignature.Broadcast(ESlateVisibility::Hidden);
			FInputModeGameOnly InputMode;
			PC->SetInputMode(InputMode);
			PC->bShowMouseCursor = false;

			bMenuWidgetOpened = false;
		}

		//GetInGameOverlayWidget();


		break;
	case EGameState::InGameMenu:		
		//GetMenuWidget();
		MenuWidgetController->CurrentMenuType = MenuType;
		MenuWidgetController->OnSwitchWidget.Broadcast(MenuType);
		MenuWidgetController->OnSetVisibilitySignature.Broadcast(ESlateVisibility::Visible);

		FInputModeGameAndUI InputMode = FInputModeGameAndUI();
		//InputMode.SetWidgetToFocus(MenuWidget->TakeWidget());
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
		PC->SetInputMode(InputMode);
		bMenuWidgetOpened = true;
				
		break;
		
	}
	Cast<ASCPlayerController>(PC)->SwitchInputMode(GameState);
	CurrentGameState = GameState;
}




void ASCHUD::ToggleInGameMenu(EMenuType MenuType)
{
	if (bCanOpenInToggleMenu)
	{
		bCanOpenInToggleMenu = false;
		if (CurrentGameState == EGameState::InGameMenu)
		{			
			check(MenuWidgetController);
			if (MenuWidgetController->CurrentMenuType == MenuType)
			{
				DisplayGameWidget(EGameState::Playing, MenuType);
				bCanOpenInToggleMenu = true;
			}
			else
			{
				MenuWidgetController->CurrentMenuType = MenuType;
				MenuWidgetController->OnSwitchWidget.Broadcast(MenuType);
				bCanOpenInToggleMenu = true;
			}
		}
		else
		{
			DisplayGameWidget(EGameState::InGameMenu, MenuType);
			bCanOpenInToggleMenu = true;
		}

	}
}

USCMenuWidget* ASCHUD::GetMenuWidget()
{
	if(!MenuWidget)
	{
		if (!MenuWidgetController)
		{
			MenuWidgetController = GetMenuWidgetController(WidgetControllerParams);
			check(MenuWidgetController);
		}
		MenuWidget = CreateWidget<USCMenuWidget>(GetWorld(), MenuWidgetClass);
		MenuWidget->SetWidgetController(MenuWidgetController);
	}

	return MenuWidget;
}

USCInGameOverlayWidget* ASCHUD::GetInGameOverlayWidget()
{
	if (!InGameOverlayWidget)
	{
		if (!InGameOverlayWidgetController)
		{
			InGameOverlayWidgetController = GetInGameOverlayWidgetController(WidgetControllerParams);
			check(InGameOverlayWidgetController);
		}
		InGameOverlayWidget = CreateWidget<USCInGameOverlayWidget>(GetWorld(), InGameOverlayClass);
		InGameOverlayWidget->SetWidgetController(InGameOverlayWidgetController);
	}
	return InGameOverlayWidget;
}


