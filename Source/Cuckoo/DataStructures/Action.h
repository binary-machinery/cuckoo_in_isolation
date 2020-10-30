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
        bool HasUnlimitedActivations() const;
        float GetDeltaWellBeing() const;
        float GetDiminishingReturnModifier() const;

    private:
        TArray<EStateKey> Preconditions;
        TArray<EStateKey> StatesToRemove;
        TArray<EStateKey> StatesToAdd;
        FText MenuText;
        FText ResultText;
        bool bUnlimitedActivations;
        float DeltaWellBeing;
        float DiminishingReturnModifier = 1.0f;

        friend class FActionBuilder;
    };

    class FActionBuilder
    {
    public:
        FActionBuilder();
        ~FActionBuilder();

        FActionBuilder& CheckPrecondition(EStateKey Precondition);
        FActionBuilder& RemoveState(EStateKey StateKey);
        FActionBuilder& AddStates(EStateKey StateKey);
        FActionBuilder& ShowMenuText(const FText& Value);
        FActionBuilder& ShowResultText(const FText& ResultText);
        FActionBuilder& HasUnlimitedActivations(bool Value);
        FActionBuilder& SetDeltaWellBeing(float Value);
        FActionBuilder& SetDiminishingReturnModifier(float Value);
        FAction* Build();

    private:
        FAction* Action;
    };
}
