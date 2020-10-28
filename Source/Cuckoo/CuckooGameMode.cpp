// Copyright Epic Games, Inc. All Rights Reserved.


#include "CuckooGameMode.h"

#include "ActionsCollection.h"
#include "Blueprint/UserWidget.h"
#include "DataStructures/StateKey.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
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

void ACuckooGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
    Super::InitGame(MapName, Options, ErrorMessage);
    GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5, FColor::White,
                                     TEXT("InitGame: " + MapName + ", " + Options + ", " + ErrorMessage));
}

void ACuckooGameMode::InitGameState()
{
    Super::InitGameState();
    GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5, FColor::White, TEXT("InitGameState"));

    // Initial state
    State.Add(Cuckoo::EStateKey::HasTvWithOneChannel);
    State.Add(Cuckoo::EStateKey::HasBadInternet);

    Actions = Cuckoo::FActionsCollection().Create();
}

void ACuckooGameMode::BeginPlay()
{
    GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5, FColor::White, TEXT("BeginPlay"));

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

    GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5, FColor::White, TEXT("Create widget"));
    UUserWidget* Widget = CreateWidget<UUserWidget>(GetGameInstance(), HUDObjClass);
    Widget->AddToViewport();
    GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5, FColor::White, TEXT("Widget created"));

    ActionWidgets[0].Button->OnClicked.AddDynamic(this, &ACuckooGameMode::OnClickActionOption1Button);
    ActionWidgets[1].Button->OnClicked.AddDynamic(this, &ACuckooGameMode::OnClickActionOption2Button);
    ActionWidgets[2].Button->OnClicked.AddDynamic(this, &ACuckooGameMode::OnClickActionOption3Button);

    CurrentDay = 1;
    UpdateCurrentActionOptions();
}

void ACuckooGameMode::AddActionWidget(UButton* Button, UTextBlock* TextBlock)
{
    ActionWidgets.Add(FActionWidget(Button, TextBlock));
}

void ACuckooGameMode::SetDayTextWidget(UTextBlock* TextBlock)
{
    DayTextWidget = TextBlock;
}

void ACuckooGameMode::UpdateCurrentActionOptions()
{
    GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5, FColor::White, TEXT("Update current action options"));
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
        ActionWidgets[i].TextBlock->SetText(CurrentActionOptions[i]->GetMenuText());
    }
    for (int i = CurrentActionOptions.Num(); i < ActionWidgets.Num(); ++i)
    {
        ActionWidgets[i].TextBlock->SetText(FText::FromString(TEXT("-")));
    }
}

void ACuckooGameMode::UpdateCurrentDay()
{
    GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5, FColor::White, TEXT("Update current day"));
    ++CurrentDay;
    DayTextWidget->SetText(FText::FromString(FString::FromInt(CurrentDay)));
}

void ACuckooGameMode::PickActionOptionAndAdvanceTime(int Index)
{
    GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5, FColor::White,
                                     TEXT("Pick action option: " + FString::FromInt(Index)));
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

    UpdateCurrentActionOptions();
    UpdateCurrentDay();
}

void ACuckooGameMode::OnClickActionOption1Button()
{
    PickActionOptionAndAdvanceTime(0);
}

void ACuckooGameMode::OnClickActionOption2Button()
{
    PickActionOptionAndAdvanceTime(1);
}

void ACuckooGameMode::OnClickActionOption3Button()
{
    PickActionOptionAndAdvanceTime(2);
}
