// Copyright Epic Games, Inc. All Rights Reserved.


#include "CuckooGameMode.h"

#include "ActionsCollection.h"
#include "Blueprint/UserWidget.h"
#include "DataStructures/StateKey.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

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

    this->Actions = Cuckoo::FActionsCollection().Create();
}

void ACuckooGameMode::BeginPlay()
{
    GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5, FColor::White, TEXT("BeginPlay"));

    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    if (PlayerController)
    {
        PlayerController->bShowMouseCursor = true;
    }

    if (HUDObjClass)
    {
        GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5, FColor::White, TEXT("Create widget"));
        UUserWidget* Widget = CreateWidget<UUserWidget>(GetGameInstance(), HUDObjClass);
        Widget->AddToViewport();
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5, FColor::White, TEXT("Widget class not found"));
    }
}

void ACuckooGameMode::SetUTextBlock(UTextBlock* TextBlock)
{
    GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5, FColor::White, TextBlock->GetText().ToString());
}
