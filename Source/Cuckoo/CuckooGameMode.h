// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DataStructures/Action.h"
#include "DataStructures/StateKey.h"
#include "GameFramework/GameModeBase.h"
#include "CuckooGameMode.generated.h"

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

    virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
    virtual void InitGameState() override;
    virtual void BeginPlay() override;

    UFUNCTION(BlueprintCallable, Category="UI")
    void AddActionWidget(UButton* Button, UTextBlock* TextBlock);

    UFUNCTION(BlueprintCallable, Category="UI")
    void SetDayTextWidget(UTextBlock* TextBlock);

    UFUNCTION(BlueprintCallable, Category="UI")
    void SetWellBeingTextWidget(UTextBlock* TextBlock);

private:
    UClass* HUDObjClass;
    TArray<FActionWidget> ActionWidgets;
    UTextBlock* DayTextWidget;
    UTextBlock* WellBeingTextWidget;
    TSet<Cuckoo::EStateKey> State;
    TArray<Cuckoo::FAction*> Actions;
    int WellBeing;
    int CurrentDay;
    TArray<Cuckoo::FAction*> CurrentActionOptions;

    void UpdateCurrentActionOptions();
    void UpdateWellBeing(int DeltaValue);
    void UpdateCurrentDay();
    void PickActionOptionAndAdvanceTime(int Index);

    UFUNCTION()
    void OnClickActionOption1Button();

    UFUNCTION()
    void OnClickActionOption2Button();

    UFUNCTION()
    void OnClickActionOption3Button();
};
