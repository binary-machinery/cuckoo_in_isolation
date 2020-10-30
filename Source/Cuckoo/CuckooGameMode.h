// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DataStructures/Action.h"
#include "DataStructures/RandomEvent.h"
#include "DataStructures/StateKey.h"
#include "GameFramework/GameModeBase.h"
#include "CuckooGameMode.generated.h"

class UPanelWidget;
class UButton;
class UTextBlock;

class FActionWidget
{
public:
    FActionWidget(UButton* Button, UTextBlock* TextBlock);

    UButton* Button;
    UTextBlock* TextBlock;
};

UCLASS(Blueprintable)
class CUCKOO_API ACuckooGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    ACuckooGameMode();

    virtual void InitGameState() override;
    virtual void BeginPlay() override;

    UFUNCTION(BlueprintCallable, Category="UI")
    void SetActionOptionsPanel(UPanelWidget* Panel);

    UFUNCTION(BlueprintCallable, Category="UI")
    void SetResultTextPanel(UPanelWidget* Panel);

    UFUNCTION(BlueprintCallable, Category="UI")
    void AddActionWidget(UButton* Button, UTextBlock* TextBlock);

    UFUNCTION(BlueprintCallable, Category="UI")
    void SetDayTextWidget(UTextBlock* TextBlock);

    UFUNCTION(BlueprintCallable, Category="UI")
    void SetWellBeingTextWidget(UTextBlock* TextBlock);

    UFUNCTION(BlueprintCallable, Category="UI")
    void SetResultWidgets(UButton* ContinueButton, UTextBlock* ResultTextBlock);

private:
    UClass* HUDObjClass;
    UPanelWidget* ActionOptionsPanel;
    UPanelWidget* ResultTextPanel;
    TArray<FActionWidget> ActionWidgets;
    UTextBlock* DayTextWidget;
    UTextBlock* WellBeingTextWidget;
    UTextBlock* ResultTextWidget;
    UButton* ResultContinueButton;
    TSet<Cuckoo::EStateKey> State;
    TArray<Cuckoo::FAction*> Actions;
    TArray<Cuckoo::FRandomEvent*> RandomEvents;
    TArray<Cuckoo::FAction*> CurrentActionOptions;
    int WellBeing;
    int CurrentDay;
    bool bShowActionResult;

    void UpdateCurrentActionOptions();
    void UpdateWellBeing(int DeltaValue);
    void UpdateCurrentDay();
    void AdvanceTime();
    void PickActionOption(int Index);
    void ShowRandomEvent();

    UFUNCTION()
    void OnClickActionOption1Button();

    UFUNCTION()
    void OnClickActionOption2Button();

    UFUNCTION()
    void OnClickActionOption3Button();

    UFUNCTION()
    void OnClickResultContinueButton();
};
