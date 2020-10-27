// Copyright Epic Games, Inc. All Rights Reserved.


#include "CuckooGameMode.h"

#include "ActionsCollection.h"
#include "Blueprint/UserWidget.h"
#include "DataStructures/StateKey.h"
#include "Components/TextBlock.h"
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

    for (int i = 0; i < ActionWidgets.Num(); ++i)
    {
        ActionWidgets[i].TextBlock->SetText(Actions[i]->GetMenuText());
    }
}

void ACuckooGameMode::AddActionWidget(UButton* Button, UTextBlock* TextBlock)
{
    GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5, FColor::White, TextBlock->GetText().ToString());
    ActionWidgets.Add(FActionWidget(Button, TextBlock));
}
