#pragma once

#include "StateKey.h"
#include "Internationalization/Text.h"

namespace Cuckoo
{
    class FAction
    {
    public:
        const TArray<EStateKey>& GetPreconditions() const;
        const TArray<EStateKey>& GetStatesToRemove() const;
        const TArray<EStateKey>& GetStatesToAdd() const;
        const FText& GetMenuText() const;
        const FText& GetResultText() const;

    private:
        TArray<EStateKey> Preconditions;
        TArray<EStateKey> StatesToRemove;
        TArray<EStateKey> StatesToAdd;
        FText MenuText;
        FText ResultText;

        friend class FActionBuilder;
    };

    class FActionBuilder
    {
    public:
        FActionBuilder& CheckPrecondition(EStateKey Precondition);
        FActionBuilder& RemoveState(EStateKey StateKey);
        FActionBuilder& AddStates(EStateKey StateKey);
        FActionBuilder& ShowMenuText(const FText& Value);
        FActionBuilder& ShowResultText(const FText& ResultText);
        FAction* Build();

    private:
        TArray<EStateKey> Preconditions;
        TArray<EStateKey> StatesToRemove;
        TArray<EStateKey> StatesToAdd;
        FText MenuText;
        FText ResultText;
    };
}
