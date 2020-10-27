#pragma once
#include "StateKey.h"
#include "Internationalization/Text.h"

namespace Cuckoo
{
    class FAction
    {
    public:
        const TArray<EStateKey>& GetPreconditions();
        const TArray<EStateKey>& GetStatesToRemove();
        const TArray<EStateKey>& GetStatesToAdd();
        const FText& GetMenuText();
        const FText& GetResultText();

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
        FActionBuilder& AddPrecondition(EStateKey Precondition);
        FActionBuilder& AddStatesToRemove(EStateKey StateKey);
        FActionBuilder& AddStatesToAdd(EStateKey StateKey);
        FActionBuilder& SetMenuText(const FText& Value);
        FActionBuilder& SetResultText(const FText& ResultText);
        FAction* Build();
    
    private:
        TArray<EStateKey> Preconditions;
        TArray<EStateKey> StatesToRemove;
        TArray<EStateKey> StatesToAdd;
        FText MenuText;
        FText ResultText;
    };
}
