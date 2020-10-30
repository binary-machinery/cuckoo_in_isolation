#include "ActionsCollection.h"


TArray<Cuckoo::FAction*> Cuckoo::FActionsCollection::Create()
{
    TArray<FAction*> Actions;

    Actions.Add(
        FActionBuilder().ShowMenuText(FText::FromString(TEXT("Посмотреть телевизор")))
                        .ShowResultText(FText::FromString(TEXT("Посмотрел")))
                        .CheckPrecondition(EStateKey::HasTvWithOneChannel)
                        .AddStates(EStateKey::BelievesInPropaganda)
                        .HasUnlimitedActivations(true)
                        .SetDeltaWellBeing(5)
                        .SetDiminishingReturnModifier(2)
                        .Build()
    );

    Actions.Add(
        FActionBuilder().ShowMenuText(FText::FromString(TEXT("Подключить больше каналов на телевизоре")))
                        .ShowResultText(FText::FromString(TEXT("Подключил")))
                        .CheckPrecondition(EStateKey::HasTvWithOneChannel)
                        .RemoveState(EStateKey::HasTvWithOneChannel)
                        .RemoveState(EStateKey::BelievesInPropaganda)
                        .AddStates(EStateKey::HasTvWithManyChannels)
                        .SetDeltaWellBeing(8)
                        .Build()
    );

    Actions.Add(
        FActionBuilder().ShowMenuText(FText::FromString(TEXT("Посмотреть телевизор")))
                        .ShowResultText(FText::FromString(TEXT("Посмотрел")))
                        .CheckPrecondition(EStateKey::HasTvWithManyChannels)
                        .HasUnlimitedActivations(true)
                        .SetDeltaWellBeing(10)
                        .SetDiminishingReturnModifier(1.3)
                        .Build()
    );

    Actions.Add(
        FActionBuilder().ShowMenuText(FText::FromString(TEXT("Обновить тариф и взять интернет побыстрее")))
                        .ShowResultText(FText::FromString(TEXT("Подключил")))
                        .CheckPrecondition(EStateKey::HasBadInternet)
                        .RemoveState(EStateKey::HasBadInternet)
                        .AddStates(EStateKey::HasGoodInternet)
                        .SetDeltaWellBeing(7)
                        .Build()
    );

    Actions.Add(
        FActionBuilder().ShowMenuText(FText::FromString(TEXT("Подписаться на стриминговый сервис")))
                        .ShowResultText(FText::FromString(TEXT("Подписался")))
                        .AddStates(EStateKey::HasStreamingSubscription)
                        .SetDeltaWellBeing(10)
                        .Build()
    );

    Actions.Add(
        FActionBuilder().ShowMenuText(FText::FromString(TEXT("Посмотреть стриминговый сервис")))
                        .ShowResultText(FText::FromString(TEXT("Посмотрел")))
                        .CheckPrecondition(EStateKey::HasStreamingSubscription)
                        .AddStates(EStateKey::HasFavoriteSeries)
                        .HasUnlimitedActivations(true)
                        .SetDeltaWellBeing(8)
                        .SetDiminishingReturnModifier(1.3)
                        .Build()
    );

    Actions.Add(
        FActionBuilder().ShowMenuText(FText::FromString(TEXT("Взять премиумную подписку на стриминговый сервис")))
                        .ShowResultText(FText::FromString(TEXT("Подписался на премиум")))
                        .CheckPrecondition(EStateKey::HasStreamingSubscription)
                        .RemoveState(EStateKey::HasStreamingSubscription)
                        .AddStates(EStateKey::HasPremiumStreamingSubscription)
                        .SetDeltaWellBeing(10)
                        .Build()
    );

    Actions.Add(
        FActionBuilder().ShowMenuText(FText::FromString(TEXT("Посмотреть стриминговый сервис")))
                        .ShowResultText(FText::FromString(TEXT("Посмотрел")))
                        .CheckPrecondition(EStateKey::HasPremiumStreamingSubscription)
                        .AddStates(EStateKey::HasFavoriteSeries)
                        .HasUnlimitedActivations(true)
                        .SetDeltaWellBeing(10)
                        .SetDiminishingReturnModifier(1.2)
                        .Build()
    );

    Actions.Add(
        FActionBuilder().ShowMenuText(FText::FromString(TEXT("Купить игровую консоль")))
                        .ShowResultText(FText::FromString(TEXT("Купил")))
                        .AddStates(EStateKey::HasGamingConsole)
                        .SetDeltaWellBeing(10)
                        .Build()
    );

    Actions.Add(
        FActionBuilder().ShowMenuText(FText::FromString(TEXT("Поиграть в видеоигры")))
                        .ShowResultText(FText::FromString(TEXT("Поиграл")))
                        .CheckPrecondition(EStateKey::HasGamingConsole)
                        .AddStates(EStateKey::HasFavoriteGame)
                        .HasUnlimitedActivations(true)
                        .SetDeltaWellBeing(8)
                        .SetDiminishingReturnModifier(1.1)
                        .Build()
    );

    Actions.Add(
        FActionBuilder().ShowMenuText(FText::FromString(TEXT("Поиграть в онлайн-видеоигры")))
                        .ShowResultText(FText::FromString(TEXT("Поиграл, но было плохо")))
                        .CheckPrecondition(EStateKey::HasGamingConsole)
                        .CheckPrecondition(EStateKey::HasBadInternet)
                        .SetDeltaWellBeing(3)
                        .Build()
    );

    Actions.Add(
        FActionBuilder().ShowMenuText(FText::FromString(TEXT("Поиграть в онлайн-видеоигры")))
                        .ShowResultText(FText::FromString(TEXT("Поиграл")))
                        .CheckPrecondition(EStateKey::HasGamingConsole)
                        .CheckPrecondition(EStateKey::HasGoodInternet)
                        .SetDeltaWellBeing(8)
                        .Build()
    );

    Actions.Add(
        FActionBuilder().ShowMenuText(FText::FromString(TEXT("Завести хобби")))
                        .ShowResultText(FText::FromString(TEXT("Завел")))
                        .AddStates(EStateKey::HasHobby)
                        .SetDeltaWellBeing(10)
                        .Build()
    );

    Actions.Add(
        FActionBuilder().ShowMenuText(FText::FromString(TEXT("Заняться своим хобби")))
                        .ShowResultText(FText::FromString(TEXT("Занялся")))
                        .CheckPrecondition(EStateKey::HasHobby)
                        .AddStates(EStateKey::GoodAtHobby)
                        .HasUnlimitedActivations(true)
                        .SetDeltaWellBeing(8)
                        .SetDiminishingReturnModifier(1.2)
                        .Build()
    );

    Actions.Add(
        FActionBuilder().ShowMenuText(FText::FromString(TEXT("Поучаствовать в конкурсе, связанном с хобби")))
                        .ShowResultText(FText::FromString(TEXT("Поучаствовал")))
                        .CheckPrecondition(EStateKey::GoodAtHobby)
                        .SetDeltaWellBeing(10)
                        .Build()
    );

    Actions.Add(
        FActionBuilder().ShowMenuText(FText::FromString(TEXT("Завести блог")))
                        .ShowResultText(FText::FromString(TEXT("Завел")))
                        .AddStates(EStateKey::HasBlog)
                        .SetDeltaWellBeing(10)
                        .Build()
    );

    Actions.Add(
        FActionBuilder().ShowMenuText(FText::FromString(TEXT("Написать в блог про самоизоляцию")))
                        .ShowResultText(FText::FromString(TEXT("Написал")))
                        .CheckPrecondition(EStateKey::HasBlog)
                        .SetDeltaWellBeing(5)
                        .Build()
    );

    Actions.Add(
        FActionBuilder().ShowMenuText(FText::FromString(TEXT("Написать в блог про свою любимую игру")))
                        .ShowResultText(FText::FromString(TEXT("Написал")))
                        .CheckPrecondition(EStateKey::HasBlog)
                        .CheckPrecondition(EStateKey::HasFavoriteGame)
                        .SetDeltaWellBeing(7)
                        .Build()
    );

    Actions.Add(
        FActionBuilder().ShowMenuText(FText::FromString(TEXT("Написать в блог про свою любимую игровую консоль")))
                        .ShowResultText(FText::FromString(TEXT("Написал")))
                        .CheckPrecondition(EStateKey::HasBlog)
                        .CheckPrecondition(EStateKey::HasGamingConsole)
                        .AddStates(EStateKey::ConsoleWarrior)
                        .SetDeltaWellBeing(7)
                        .Build()
    );

    Actions.Add(
        FActionBuilder().ShowMenuText(FText::FromString(TEXT("Написать в блог про свой любимый сериал")))
                        .ShowResultText(FText::FromString(TEXT("Написал")))
                        .CheckPrecondition(EStateKey::HasBlog)
                        .CheckPrecondition(EStateKey::HasFavoriteSeries)
                        .SetDeltaWellBeing(7)
                        .Build()
    );

    Actions.Add(
        FActionBuilder().ShowMenuText(
                            FText::FromString(TEXT("Написать в блог про то, что твой любимый сериал закрыли")))
                        .ShowResultText(FText::FromString(TEXT("Написал")))
                        .CheckPrecondition(EStateKey::HasBlog)
                        .CheckPrecondition(EStateKey::FavoriteSeriesClosed)
                        .SetDeltaWellBeing(8)
                        .Build()
    );

    Actions.Add(
        FActionBuilder().ShowMenuText(FText::FromString(TEXT("Написать в блог про свое хобби")))
                        .ShowResultText(FText::FromString(TEXT("Написал")))
                        .CheckPrecondition(EStateKey::HasBlog)
                        .CheckPrecondition(EStateKey::HasHobby)
                        .SetDeltaWellBeing(8)
                        .Build()
    );

    Actions.Add(
        FActionBuilder().ShowMenuText(FText::FromString(TEXT("Написать в блог про свои успехи в хобби")))
                        .ShowResultText(FText::FromString(TEXT("Написал")))
                        .CheckPrecondition(EStateKey::HasBlog)
                        .CheckPrecondition(EStateKey::GoodAtHobby)
                        .SetDeltaWellBeing(10)
                        .Build()
    );

    Actions.Add(
        FActionBuilder().ShowMenuText(FText::FromString(TEXT("Написать в блог про домашнее животное")))
                        .ShowResultText(FText::FromString(TEXT("Написал")))
                        .CheckPrecondition(EStateKey::HasBlog)
                        .CheckPrecondition(EStateKey::HasPet)
                        .SetDeltaWellBeing(10)
                        .Build()
    );

    Actions.Add(
        FActionBuilder().ShowMenuText(FText::FromString(TEXT("Написать в блог про домашних животных")))
                        .ShowResultText(FText::FromString(TEXT("Написал")))
                        .CheckPrecondition(EStateKey::HasBlog)
                        .CheckPrecondition(EStateKey::HasThreePets)
                        .SetDeltaWellBeing(10)
                        .Build()
    );

    Actions.Add(
        FActionBuilder().ShowMenuText(FText::FromString(TEXT("Завести домашнее животное")))
                        .ShowResultText(FText::FromString(TEXT("Завел")))
                        .AddStates(EStateKey::HasPet)
                        .SetDeltaWellBeing(10)
                        .Build()
    );

    Actions.Add(
        FActionBuilder().ShowMenuText(FText::FromString(TEXT("Завести еще одно домашнее животное")))
                        .ShowResultText(FText::FromString(TEXT("Завел")))
                        .CheckPrecondition(EStateKey::HasPet)
                        .AddStates(EStateKey::HasTwoPets)
                        .SetDeltaWellBeing(10)
                        .Build()
    );

    Actions.Add(
        FActionBuilder().ShowMenuText(FText::FromString(TEXT("Завести еще одно домашнее животное")))
                        .ShowResultText(FText::FromString(TEXT("Завел")))
                        .CheckPrecondition(EStateKey::HasTwoPets)
                        .RemoveState(EStateKey::HasTwoPets)
                        .AddStates(EStateKey::HasThreePets)
                        .SetDeltaWellBeing(10)
                        .Build()
    );


    return MoveTemp(Actions);
}
