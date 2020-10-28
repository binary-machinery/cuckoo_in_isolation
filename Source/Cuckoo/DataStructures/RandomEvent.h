#pragma once

#include "StateKey.h"
#include "Internationalization/Text.h"

namespace Cuckoo
{
    class FRandomEvent
    {
    public:
        const TArray<EStateKey>& GetPreconditions() const;
        const TArray<EStateKey>& GetStatesToRemove() const;
        const TArray<EStateKey>& GetStatesToAdd() const;
        const FText& GetResultText() const;

    private:
        TArray<EStateKey> Preconditions;
        TArray<EStateKey> StatesToRemove;
        TArray<EStateKey> StatesToAdd;
        FText ResultText;

        friend class FRandomEventBuilder;
    };

    class FRandomEventBuilder
    {
    public:
        FRandomEventBuilder& CheckPrecondition(EStateKey Precondition);
        FRandomEventBuilder& RemoveState(EStateKey StateKey);
        FRandomEventBuilder& AddState(EStateKey StateKey);
        FRandomEventBuilder& ShowResultText(const FText& ResultText);
        FRandomEvent* Build();

    private:
        TArray<EStateKey> Preconditions;
        TArray<EStateKey> StatesToRemove;
        TArray<EStateKey> StatesToAdd;
        FText ResultText;
    };
}
