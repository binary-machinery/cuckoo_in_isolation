#include "ActionsCollection.h"


TArray<Cuckoo::FAction*> Cuckoo::FActionsCollection::Create()
{
    TArray<FAction*> Actions;

    Actions.Add(
        FActionBuilder().SetMenuText(FText::FromString(TEXT("Посмотреть телевизор")))
                        .SetResultText(FText::FromString(TEXT("Посмотрел")))
                        .AddPrecondition(EStateKey::HasTvWithOneChannel)
                        .AddStatesToAdd(EStateKey::BelievesInPropaganda)
                        .Build()
    );

    Actions.Add(
        FActionBuilder().SetMenuText(FText::FromString(TEXT("Посмотреть телевизор")))
                        .SetResultText(FText::FromString(TEXT("Посмотрел")))
                        .AddPrecondition(EStateKey::HasTvWithManyChannels)
                        .Build()
    );

    Actions.Add(
        FActionBuilder().SetMenuText(FText::FromString(TEXT("Подписаться на стриминговый сервис")))
                        .SetResultText(FText::FromString(TEXT("Подписался")))
                        .AddStatesToAdd(EStateKey::HasStreamingSubscription)
                        .Build()
    );

    Actions.Add(
        FActionBuilder().SetMenuText(FText::FromString(TEXT("Посмотреть стриминговый сервис")))
                        .SetResultText(FText::FromString(TEXT("Посмотрел")))
                        .AddPrecondition(EStateKey::HasStreamingSubscription)
                        .Build()
    );

    Actions.Add(
        FActionBuilder().SetMenuText(FText::FromString(TEXT("Взять премиумную подписку стриминговый сервис")))
                        .SetResultText(FText::FromString(TEXT("Подписался на премиум")))
                        .AddPrecondition(EStateKey::HasStreamingSubscription)
                        .AddStatesToAdd(EStateKey::HasPremiumStreamingSubscription)
                        .Build()
    );

    Actions.Add(
        FActionBuilder().SetMenuText(FText::FromString(TEXT("Купить игровую консоль")))
                        .SetResultText(FText::FromString(TEXT("Купил")))
                        .AddStatesToAdd(EStateKey::HasGamingConsole)
                        .Build()
    );

    return MoveTemp(Actions);
}
