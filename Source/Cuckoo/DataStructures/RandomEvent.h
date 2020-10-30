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
        float GetDeltaWellBeing() const;

    private:
        TArray<EStateKey> Preconditions;
        TArray<EStateKey> StatesToRemove;
        TArray<EStateKey> StatesToAdd;
        FText ResultText;
        float DeltaWellBeing;

        friend class FRandomEventBuilder;
    };

    class FRandomEventBuilder
    {
    public:
        FRandomEventBuilder();
        ~FRandomEventBuilder();
        
        FRandomEventBuilder& CheckPrecondition(EStateKey Precondition);
        FRandomEventBuilder& RemoveState(EStateKey StateKey);
        FRandomEventBuilder& AddState(EStateKey StateKey);
        FRandomEventBuilder& ShowResultText(const FText& ResultText);
        FRandomEventBuilder& SetDeltaWellBeing(float Value);
        FRandomEvent* Build();

    private:
        FRandomEvent* Event;
    };
}
