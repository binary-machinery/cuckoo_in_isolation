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

    CurrentActionOptions = GetActionOptions();
    for (int i = 0; i < CurrentActionOptions.Num(); ++i)
    {
        ActionWidgets[i].TextBlock->SetText(CurrentActionOptions[i]->GetMenuText());
    }
}

void ACuckooGameMode::AddActionWidget(UButton* Button, UTextBlock* TextBlock)
{
    GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5, FColor::White, TextBlock->GetText().ToString());
    ActionWidgets.Add(FActionWidget(Button, TextBlock));
}

TArray<Cuckoo::FAction*> ACuckooGameMode::GetActionOptions() const
{
    TArray<Cuckoo::FAction*> FilteredActions;
    for (auto Action : Actions)
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
            GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5, FColor::White, TEXT("Not enough options: " + i));
            break;
        }
        const int Index = FMath::RandRange(0, FilteredActions.Num() - 1);
        Result.Add(FilteredActions[Index]);
        FilteredActions.RemoveAt(Index);
    }
    return MoveTemp(Result);
}

void ACuckooGameMode::PickActionOption(int Index)
{
    GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5, FColor::White, TEXT("Pick action option: " + FString::FromInt(Index)));
    if (Index >= CurrentActionOptions.Num())
    {
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
