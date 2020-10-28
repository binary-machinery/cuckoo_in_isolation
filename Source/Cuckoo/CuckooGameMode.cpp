// Copyright Epic Games, Inc. All Rights Reserved.


#include "CuckooGameMode.h"

#include "ActionsCollection.h"
#include "RandomEventCollection.h"
#include "Blueprint/UserWidget.h"
#include "DataStructures/StateKey.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "DataStructures/RandomEvent.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

FActionWidget::FActionWidget(UButton* Button, UTextBlock* TextBlock)
{
    this->Button = Button;
    this->TextBlock = TextBlock;
}

ACuckooGameMode::ACuckooGameMode()
{
    static ConstructorHelpers::FClassFinder<UUserWidget> HUDWidgetObj(TEXT("/Game/UI/WBP_HUD"));
    if (HUDWidgetObj.Succeeded())
    {
        HUDObjClass = HUDWidgetObj.Class;
    }
}

void ACuckooGameMode::InitGameState()
{
    Super::InitGameState();

    State.Add(Cuckoo::EStateKey::HasTvWithOneChannel);
    State.Add(Cuckoo::EStateKey::HasBadInternet);

    WellBeing = 50;
    CurrentDay = 0;

    Actions = Cuckoo::FActionsCollection().Create();
    RandomEvents = Cuckoo::FRandomEventCollection().Create();
}

void ACuckooGameMode::BeginPlay()
{
    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    if (PlayerController)
    {
        PlayerController->bShowMouseCursor = true;
    }

    if (!HUDObjClass)
    {
        GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5, FColor::White, TEXT("Widget class not found"));
        return;
    }

    UUserWidget* Widget = CreateWidget<UUserWidget>(GetGameInstance(), HUDObjClass);
    Widget->AddToViewport();

    ActionWidgets[0].Button->OnClicked.AddDynamic(this, &ACuckooGameMode::OnClickActionOption1Button);
    ActionWidgets[1].Button->OnClicked.AddDynamic(this, &ACuckooGameMode::OnClickActionOption2Button);
    ActionWidgets[2].Button->OnClicked.AddDynamic(this, &ACuckooGameMode::OnClickActionOption3Button);

    ResultContinueButton->OnClicked.AddDynamic(this, &ACuckooGameMode::OnClickResultContinueButton);

    UpdateWellBeing(0);
    UpdateCurrentDay();
    UpdateCurrentActionOptions();
}

void ACuckooGameMode::SetActionOptionsPanel(UPanelWidget* Panel)
{
    ActionOptionsPanel = Panel;
}

void ACuckooGameMode::SetResultTextPanel(UPanelWidget* Panel)
{
    ResultTextPanel = Panel;
}

void ACuckooGameMode::AddActionWidget(UButton* Button, UTextBlock* TextBlock)
{
    ActionWidgets.Add(FActionWidget(Button, TextBlock));
}

void ACuckooGameMode::SetDayTextWidget(UTextBlock* TextBlock)
{
    DayTextWidget = TextBlock;
}

void ACuckooGameMode::SetWellBeingTextWidget(UTextBlock* TextBlock)
{
    WellBeingTextWidget = TextBlock;
}

void ACuckooGameMode::SetResultWidgets(UButton* ContinueButton, UTextBlock* ResultTextBlock)
{
    ResultContinueButton = ContinueButton;
    ResultTextWidget = ResultTextBlock;
}

void ACuckooGameMode::UpdateCurrentActionOptions()
{
    ResultTextPanel->SetVisibility(ESlateVisibility::Hidden);

    TArray<Cuckoo::FAction*> FilteredActions;
    for (Cuckoo::FAction* Action : Actions)
    {
        bool bAllPreconditionMatched = true;
        for (const Cuckoo::EStateKey Precondition : Action->GetPreconditions())
        {
            if (!State.Contains(Precondition))
            {
                bAllPreconditionMatched = false;
                break;
            }
        }
        if (bAllPreconditionMatched)
        {
            FilteredActions.Add(Action);
        }
    }

    TArray<Cuckoo::FAction*> Result;
    for (int i = 0; i < 3; ++i)
    {
        if (FilteredActions.Num() == 0)
        {
            GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5, FColor::White,
                                             TEXT("Not enough options: " + FString::FromInt(i)));
            break;
        }
        const int Index = FMath::RandRange(0, FilteredActions.Num() - 1);
        Result.Add(FilteredActions[Index]);
        FilteredActions.RemoveAt(Index);
    }

    CurrentActionOptions = MoveTemp(Result);
    for (int i = 0; i < CurrentActionOptions.Num(); ++i)
    {
        ActionWidgets[i].Button->SetVisibility(ESlateVisibility::Visible);
        ActionWidgets[i].TextBlock->SetText(CurrentActionOptions[i]->GetMenuText());
    }
    for (int i = CurrentActionOptions.Num(); i < ActionWidgets.Num(); ++i)
    {
        ActionWidgets[i].TextBlock->SetText(FText::FromString(TEXT("-")));
        ActionWidgets[i].Button->SetVisibility(ESlateVisibility::Hidden);
    }

    ActionOptionsPanel->SetVisibility(ESlateVisibility::Visible);
}

void ACuckooGameMode::UpdateWellBeing(int DeltaValue)
{
    WellBeing += DeltaValue;
    WellBeingTextWidget->SetText(FText::FromString(FString::FromInt(WellBeing)));
}

void ACuckooGameMode::UpdateCurrentDay()
{
    ++CurrentDay;
    DayTextWidget->SetText(FText::FromString(FString::FromInt(CurrentDay)));
}

void ACuckooGameMode::PickActionOption(int Index)
{
    ActionOptionsPanel->SetVisibility(ESlateVisibility::Hidden);

    if (Index >= CurrentActionOptions.Num())
    {
        GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5, FColor::White,
                                         TEXT("No such option: " + FString::FromInt(Index)));
        return;
    }

    Cuckoo::FAction* Action = CurrentActionOptions[Index];
    for (const Cuckoo::EStateKey Key : Action->GetStatesToRemove())
    {
        State.Remove(Key);
    }
    for (const Cuckoo::EStateKey Key : Action->GetStatesToAdd())
    {
        State.Add(Key);
    }
    Actions.Remove(Action);

    bShowRandomEvent = false;
    ResultTextWidget->SetText(Action->GetResultText());
    ResultTextPanel->SetVisibility(ESlateVisibility::Visible);
}

void ACuckooGameMode::ShowRandomEvent()
{
    ActionOptionsPanel->SetVisibility(ESlateVisibility::Hidden);

    TArray<Cuckoo::FRandomEvent*> FilteredRandomEvents;
    for (Cuckoo::FRandomEvent* RandomEvent : RandomEvents)
    {
        bool bAllPreconditionMatched = true;
        for (const Cuckoo::EStateKey Precondition : RandomEvent->GetPreconditions())
        {
            if (!State.Contains(Precondition))
            {
                bAllPreconditionMatched = false;
                break;
            }
        }
        if (bAllPreconditionMatched)
        {
            FilteredRandomEvents.Add(RandomEvent);
        }
    }

    if (FilteredRandomEvents.Num() > 0)
    {
        const int Index = FMath::RandRange(0, FilteredRandomEvents.Num() - 1);
        Cuckoo::FRandomEvent* Event = FilteredRandomEvents[Index];
        for (const Cuckoo::EStateKey Key : Event->GetStatesToRemove())
        {
            State.Remove(Key);
        }
        for (const Cuckoo::EStateKey Key : Event->GetStatesToAdd())
        {
            State.Add(Key);
        }
        RandomEvents.Remove(Event);

        bShowRandomEvent = true;
        ResultTextWidget->SetText(Event->GetResultText());
        ResultTextPanel->SetVisibility(ESlateVisibility::Visible);
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5, FColor::White,
                                         TEXT("No events"));
        UpdateCurrentActionOptions();
    }
}

void ACuckooGameMode::OnClickActionOption1Button()
{
    PickActionOption(0);
}

void ACuckooGameMode::OnClickActionOption2Button()
{
    PickActionOption(1);
}

void ACuckooGameMode::OnClickActionOption3Button()
{
    PickActionOption(2);
}

void ACuckooGameMode::OnClickResultContinueButton()
{
    if (bShowRandomEvent)
    {
        UpdateCurrentActionOptions();
    }
    else
    {
        UpdateCurrentDay();
        ShowRandomEvent();
    }
}
