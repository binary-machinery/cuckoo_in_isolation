// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DataStructures/Action.h"
#include "DataStructures/StateKey.h"
#include "GameFramework/GameModeBase.h"
#include "CuckooGameMode.generated.h"

class UTextBlock;

UCLASS(Blueprintable)
class CUCKOO_API ACuckooGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    ACuckooGameMode();

    virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
    virtual void InitGameState() override;
    virtual void BeginPlay() override;

    UFUNCTION(BlueprintCallable, Category="Test")
    void SetUTextBlock(UTextBlock* TextBlock);

private:
    UClass* HUDObjClass;
    TSet<Cuckoo::EStateKey> State;
    TArray<Cuckoo::FAction*> Actions;
};
