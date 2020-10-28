#include "ActionsCollection.h"


TArray<Cuckoo::FAction*> Cuckoo::FActionsCollection::Create()
{
    TArray<FAction*> Actions;

    Actions.Add(
        FActionBuilder().ShowMenuText(FText::FromString(TEXT("Посмотреть телевизор")))
                        .ShowResultText(FText::FromString(TEXT("Посмотрел")))
                        .CheckPrecondition(EStateKey::HasTvWithOneChannel)
                        .AddStates(EStateKey::BelievesInPropaganda)
                        .Build()
    );

    Actions.Add(
        FActionBuilder().ShowMenuText(FText::FromString(TEXT("Посмотреть телевизор")))
                        .ShowResultText(FText::FromString(TEXT("Посмотрел")))
                        .CheckPrecondition(EStateKey::HasTvWithManyChannels)
                        .Build()
    );

    Actions.Add(
        FActionBuilder().ShowMenuText(FText::FromString(TEXT("Подписаться на стриминговый сервис")))
                        .ShowResultText(FText::FromString(TEXT("Подписался")))
                        .AddStates(EStateKey::HasStreamingSubscription)
                        .Build()
    );

    Actions.Add(
        FActionBuilder().ShowMenuText(FText::FromString(TEXT("Посмотреть стриминговый сервис")))
                        .ShowResultText(FText::FromString(TEXT("Посмотрел")))
                        .CheckPrecondition(EStateKey::HasStreamingSubscription)
                        .AddStates(EStateKey::HasFavoriteSeries)
                        .Build()
    );

    Actions.Add(
        FActionBuilder().ShowMenuText(FText::FromString(TEXT("Взять премиумную подписку стриминговый сервис")))
                        .ShowResultText(FText::FromString(TEXT("Подписался на премиум")))
                        .CheckPrecondition(EStateKey::HasStreamingSubscription)
                        .AddStates(EStateKey::HasPremiumStreamingSubscription)
                        .Build()
    );

    Actions.Add(
        FActionBuilder().ShowMenuText(FText::FromString(TEXT("Купить игровую консоль")))
                        .ShowResultText(FText::FromString(TEXT("Купил")))
                        .AddStates(EStateKey::HasGamingConsole)
                        .Build()
    );

    return MoveTemp(Actions);
}
