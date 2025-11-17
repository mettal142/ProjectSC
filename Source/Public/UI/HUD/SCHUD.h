// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SCTypes/SCEnumTypes.h"
#include "UI/WidgetController/SCWidgetController.h"
#include "SCHUD.generated.h"


class USCMenuWidget;
class UMenuWidgetController;
class USCInGameOverlayWidget;
class UInGameOverlayWidgetController;
class ASCPlayerCharacter;
class UQuickSlotWidgetController;

/**
 * 
 */
UCLASS()
class PROJECTSC_API ASCHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	void InitWidgets(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);
	void InitQuickSlotWidget(ASCPlayerCharacter* PlayerCharacter);
	void DisplayGameWidget(EGameState GameState, EMenuType MenuType);	
	void SetWidgetControllerParams(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);
	void GetWidgetControllerParams(FWidgetControllerParams& OutWCParams);

	UFUNCTION(BlueprintCallable)
	void ToggleInGameMenu(EMenuType MenuType);

	UFUNCTION(BlueprintPure, Category = "SCFunctionLibrary|WidgetController")
	UMenuWidgetController* GetMenuWidgetController(const FWidgetControllerParams& WCParams);
	UFUNCTION(BlueprintPure, Category = "SCFunctionLibrary|WidgetController")
	UInGameOverlayWidgetController* GetInGameOverlayWidgetController(const FWidgetControllerParams& WCParams);

	UFUNCTION(BlueprintPure, Category = "SCFunctionLibrary|WidgetController")
	UQuickSlotWidgetController* GetQuickSlotWidgetController();

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void HUDSet();
private:

	UPROPERTY(VisibleAnywhere)
	EGameState CurrentGameState = EGameState::Playing;
	bool bCanOpenInToggleMenu = true;
	FWidgetControllerParams WidgetControllerParams;

#pragma region MenuWidget
	USCMenuWidget* GetMenuWidget();
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USCMenuWidget> MenuWidget;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<USCMenuWidget> MenuWidgetClass;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UMenuWidgetController> MenuWidgetController;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UMenuWidgetController> MenuWidgetControllerClass;

	bool bMenuWidgetOpened = false;
	
#pragma endregion

#pragma region MenuWidget

	USCInGameOverlayWidget* GetInGameOverlayWidget();

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USCInGameOverlayWidget> InGameOverlayWidget;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<USCInGameOverlayWidget> InGameOverlayClass;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UInGameOverlayWidgetController> InGameOverlayWidgetController;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UInGameOverlayWidgetController> InGameOverlayWidgetControllerClass;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UQuickSlotWidgetController> QuickSlotWidgetController;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UQuickSlotWidgetController> QuickSlotWidgetControllerClass;
	
#pragma endregion

};
