#include "ActionsCollection.h"


TArray<Cuckoo::FAction*> Cuckoo::FActionsCollection::Create()
{
    TArray<FAction*> Actions;

    Actions.Add(
        FActionBuilder().ShowMenuText(FText::FromString(TEXT("Посмотреть телевизор")))
                        .ShowResultText(FText::FromString(TEXT(
                            "По телевизору говорят что-то про политику и как всё плохо. Жаль, что у меня всего один канал.")))
                        .CheckPrecondition(EStateKey::HasTvWithOneChannel)
                        .AddStates(EStateKey::NeedsMoreTvChannels)
                        .AddStates(EStateKey::BelievesInPropaganda)
                        .HasUnlimitedActivations(true)
                        .SetDeltaWellBeing(5)
                        .SetDiminishingReturnModifier(2)
                        .Build()
    );

    Actions.Add(
        FActionBuilder().ShowMenuText(FText::FromString(TEXT("Подключить больше каналов на телевизоре")))
                        .ShowResultText(FText::FromString(TEXT(
                            "Так уже лучше! Теперь можно смотреть что-то помимо новостей.")))
                        .CheckPrecondition(EStateKey::HasTvWithOneChannel)
                        .CheckPrecondition(EStateKey::NeedsMoreTvChannels)
                        .RemoveState(EStateKey::HasTvWithOneChannel)
                        .RemoveState(EStateKey::BelievesInPropaganda)
                        .RemoveState(EStateKey::NeedsMoreTvChannels)
                        .AddStates(EStateKey::HasTvWithManyChannels)
                        .SetDeltaWellBeing(8)
                        .Build()
    );

    Actions.Add(
        FActionBuilder().ShowMenuText(FText::FromString(TEXT("Посмотреть телевизор")))
                        .ShowResultText(FText::FromString(TEXT(
                            "О, моё любимое шоу еще не закрылось. Надо посмотреть!")))
                        .CheckPrecondition(EStateKey::HasTvWithManyChannels)
                        .HasUnlimitedActivations(true)
                        .SetDeltaWellBeing(10)
                        .SetDiminishingReturnModifier(1.3)
                        .Build()
    );

    Actions.Add(
        FActionBuilder().ShowMenuText(FText::FromString(TEXT("Обновить тариф и взять интернет побыстрее")))
                        .ShowResultText(FText::FromString(TEXT(
                            "Ну теперь-то заживём! Теперь даже видео с котиками грузятся без задержек.")))
                        .CheckPrecondition(EStateKey::NeedsBetterInternet)
                        .RemoveState(EStateKey::HasBadInternet)
                        .RemoveState(EStateKey::NeedsBetterInternet)
                        .AddStates(EStateKey::HasGoodInternet)
                        .SetDeltaWellBeing(7)
                        .Build()
    );

    Actions.Add(
        FActionBuilder().ShowMenuText(FText::FromString(TEXT("Подписаться на стриминговый сервис с сериалами")))
                        .ShowResultText(FText::FromString(TEXT(
                            "Пора уже подписаться на Flexlix. Теперь-то уж точно есть время для всех тех сериалов, которые мне было некогда смотреть!")))
                        .AddStates(EStateKey::HasStreamingSubscription)
                        .SetDeltaWellBeing(10)
                        .Build()
    );

    Actions.Add(
        FActionBuilder().ShowMenuText(FText::FromString(TEXT("Посмотреть сериал на Flexlix")))
                        .ShowResultText(FText::FromString(TEXT("Еще одна серия и я пойду спать. Честно!")))
                        .CheckPrecondition(EStateKey::HasStreamingSubscription)
                        .AddStates(EStateKey::HasFavoriteSeries)
                        .HasUnlimitedActivations(true)
                        .SetDeltaWellBeing(8)
                        .SetDiminishingReturnModifier(1.3)
                        .Build()
    );

    Actions.Add(
        FActionBuilder().ShowMenuText(FText::FromString(TEXT("Обновить подписку на стриминговый сервис до премиумной")))
                        .ShowResultText(FText::FromString(TEXT(
                            "Обновила подписку до Flexlix Superflex. Теперь можно смотреть сериалы в 8К!")))
                        .CheckPrecondition(EStateKey::HasStreamingSubscription)
                        .RemoveState(EStateKey::HasStreamingSubscription)
                        .AddStates(EStateKey::HasPremiumStreamingSubscription)
                        .SetDeltaWellBeing(10)
                        .Build()
    );

    Actions.Add(
        FActionBuilder().ShowMenuText(FText::FromString(TEXT("Посмотреть сериал на Flexlix Superflex")))
                        .ShowResultText(FText::FromString(TEXT(
                            "Я так и не поняла, почему они решили закончить сезон именно так. Ладно, что там у нас дальше?")))
                        .CheckPrecondition(EStateKey::HasPremiumStreamingSubscription)
                        .AddStates(EStateKey::HasFavoriteSeries)
                        .HasUnlimitedActivations(true)
                        .SetDeltaWellBeing(10)
                        .SetDiminishingReturnModifier(1.2)
                        .Build()
    );

    Actions.Add(
        FActionBuilder().ShowMenuText(FText::FromString(TEXT("Купить игровую консоль")))
                        .ShowResultText(FText::FromString(TEXT(
                            "Оказывается, игровые консоли бывают разные. Взяла ту, у которой больше цифр.")))
                        .AddStates(EStateKey::HasGamingConsole)
                        .SetDeltaWellBeing(10)
                        .Build()
    );

    Actions.Add(
        FActionBuilder().ShowMenuText(FText::FromString(TEXT("Поиграть в видеоигры")))
                        .ShowResultText(FText::FromString(TEXT("А? Что? Уже ночь? Еще один ход и спать!")))
                        .CheckPrecondition(EStateKey::HasGamingConsole)
                        .AddStates(EStateKey::HasFavoriteGame)
                        .HasUnlimitedActivations(true)
                        .SetDeltaWellBeing(8)
                        .SetDiminishingReturnModifier(1.1)
                        .Build()
    );

    Actions.Add(
        FActionBuilder().ShowMenuText(FText::FromString(TEXT("Поиграть в онлайн-видеоигры")))
                        .ShowResultText(FText::FromString(TEXT(
                            "Из-за лагов играть было почти невозможно. Видимо, нужен интернет побыстрее.")))
                        .CheckPrecondition(EStateKey::HasGamingConsole)
                        .CheckPrecondition(EStateKey::HasBadInternet)
                        .AddStates(EStateKey::NeedsBetterInternet)
                        .SetDeltaWellBeing(3)
                        .Build()
    );

    Actions.Add(
        FActionBuilder().ShowMenuText(FText::FromString(TEXT("Поиграть в онлайн-видеоигры")))
                        .ShowResultText(FText::FromString(TEXT(
                            "Меня несколько раз назвали аутистом, было обидно. Но было и хорошее: какие-то добрые люди передавали привет моей маме!")))
                        .CheckPrecondition(EStateKey::HasGamingConsole)
                        .CheckPrecondition(EStateKey::HasGoodInternet)
                        .SetDeltaWellBeing(8)
                        .Build()
    );

    Actions.Add(
        FActionBuilder().ShowMenuText(FText::FromString(TEXT("Завести хобби")))
                        .ShowResultText(FText::FromString(TEXT("Давно хотела заняться плетением корзинок!")))
                        .AddStates(EStateKey::HasHobby)
                        .SetDeltaWellBeing(10)
                        .Build()
    );

    Actions.Add(
        FActionBuilder().ShowMenuText(FText::FromString(TEXT("Заняться своим хобби")))
                        .ShowResultText(FText::FromString(TEXT(
                            "Я все лучше и лучше плету корзинки! Куда бы их складывать теперь?")))
                        .CheckPrecondition(EStateKey::HasHobby)
                        .AddStates(EStateKey::GoodAtHobby)
                        .HasUnlimitedActivations(true)
                        .SetDeltaWellBeing(8)
                        .SetDiminishingReturnModifier(1.2)
                        .Build()
    );

    Actions.Add(
        FActionBuilder().ShowMenuText(FText::FromString(TEXT("Поучаствовать в конкурсе, связанном с хобби")))
                        .ShowResultText(FText::FromString(TEXT(
                            "Я почти победила в конкурсе плетёных корзинок! А победитель точно накручивал голоса!")))
                        .CheckPrecondition(EStateKey::GoodAtHobby)
                        .SetDeltaWellBeing(10)
                        .Build()
    );

    Actions.Add(
        FActionBuilder().ShowMenuText(FText::FromString(TEXT("Завести блог")))
                        .ShowResultText(FText::FromString(TEXT(
                            "Кажется, мне нужно выговориться. Блог - это хорошее место для этого.")))
                        .AddStates(EStateKey::HasBlog)
                        .SetDeltaWellBeing(10)
                        .Build()
    );

    Actions.Add(
        FActionBuilder().ShowMenuText(FText::FromString(TEXT("Написать в блог про самоизоляцию")))
                        .ShowResultText(FText::FromString(TEXT(
                            "Напишу в блоге, как я провожу вечера. Сейчас всем тяжело, нужно делиться впечатлениями!")))
                        .CheckPrecondition(EStateKey::HasBlog)
                        .SetDeltaWellBeing(5)
                        .Build()
    );

    Actions.Add(
        FActionBuilder().ShowMenuText(FText::FromString(TEXT("Написать в блог про свою любимую игру")))
                        .ShowResultText(FText::FromString(TEXT(
                            "Получился отличный обзор, игра 10/10. Легко писать про любимые игры, когда у тебя хорошее настроение!")))
                        .CheckPrecondition(EStateKey::HasBlog)
                        .CheckPrecondition(EStateKey::HasFavoriteGame)
                        .SetDeltaWellBeing(7)
                        .Build()
    );

    Actions.Add(
        FActionBuilder().ShowMenuText(FText::FromString(TEXT("Написать в блог про свою любимую игровую консоль")))
                        .ShowResultText(FText::FromString(TEXT(
                            "Я написала, что лучшие консоли - это те, у которых больше цифр. А у моей консоли очень много цифр!")))
                        .CheckPrecondition(EStateKey::HasBlog)
                        .CheckPrecondition(EStateKey::HasGamingConsole)
                        .AddStates(EStateKey::ConsoleWarrior)
                        .SetDeltaWellBeing(7)
                        .Build()
    );

    Actions.Add(
        FActionBuilder().ShowMenuText(FText::FromString(TEXT("Написать в блог про свой любимый сериал")))
                        .ShowResultText(FText::FromString(TEXT("Актеры супер, сюжет супер, концовка супер!")))
                        .CheckPrecondition(EStateKey::HasBlog)
                        .CheckPrecondition(EStateKey::HasFavoriteSeries)
                        .SetDeltaWellBeing(7)
                        .Build()
    );

    Actions.Add(
        FActionBuilder().ShowMenuText(FText::FromString(TEXT("Написать в блог про закрытие любимого сериала")))
                        .ShowResultText(FText::FromString(TEXT(
                            "Как они могли так сделать? Негодяи! Надо им еще в твиттере написать!")))
                        .CheckPrecondition(EStateKey::HasBlog)
                        .CheckPrecondition(EStateKey::FavoriteSeriesClosed)
                        .SetDeltaWellBeing(8)
                        .Build()
    );

    Actions.Add(
        FActionBuilder().ShowMenuText(FText::FromString(TEXT("Написать в блог про своё хобби")))
                        .ShowResultText(FText::FromString(TEXT(
                            "В комментариях мне написали, что я плету корзинки неправильно. Нет, это они делают неправильно!")))
                        .CheckPrecondition(EStateKey::HasBlog)
                        .CheckPrecondition(EStateKey::HasHobby)
                        .SetDeltaWellBeing(8)
                        .Build()
    );

    Actions.Add(
        FActionBuilder().ShowMenuText(FText::FromString(TEXT("Написать в блог про домашнее животное")))
                        .ShowResultText(FText::FromString(TEXT(
                            "Разве она не прелесть? Весь интернет будет наполнен фотографиями моих животных!")))
                        .CheckPrecondition(EStateKey::HasBlog)
                        .CheckPrecondition(EStateKey::HasPet)
                        .SetDeltaWellBeing(10)
                        .Build()
    );

    Actions.Add(
        FActionBuilder().ShowMenuText(FText::FromString(TEXT("Написать в блог про домашних животных")))
                        .ShowResultText(FText::FromString(TEXT(
                            "В комментариях назвали сумасшедшей кошатницей. Они просто завидуют!")))
                        .CheckPrecondition(EStateKey::HasBlog)
                        .CheckPrecondition(EStateKey::HasThreePets)
                        .SetDeltaWellBeing(10)
                        .Build()
    );

    Actions.Add(
        FActionBuilder().ShowMenuText(FText::FromString(TEXT("Завести домашнее животное")))
                        .ShowResultText(FText::FromString(TEXT(
                            "Какая прелесть! Теперь она бегает по квартире, и мне не так одиноко.")))
                        .AddStates(EStateKey::HasPet)
                        .SetDeltaWellBeing(10)
                        .Build()
    );

    Actions.Add(
        FActionBuilder().ShowMenuText(FText::FromString(TEXT("Завести еще одно домашнее животное")))
                        .ShowResultText(FText::FromString(TEXT("Теперь их двое, и они могут играть друг с другом!")))
                        .CheckPrecondition(EStateKey::HasPet)
                        .AddStates(EStateKey::HasTwoPets)
                        .SetDeltaWellBeing(10)
                        .Build()
    );

    Actions.Add(
        FActionBuilder().ShowMenuText(FText::FromString(TEXT("Завести ещё одно домашнее животное")))
                        .ShowResultText(FText::FromString(TEXT(
                            "Теперь их трое - тройная милота! А та ваза мне всё равно не нравилась.")))
                        .CheckPrecondition(EStateKey::HasTwoPets)
                        .RemoveState(EStateKey::HasTwoPets)
                        .AddStates(EStateKey::HasThreePets)
                        .SetDeltaWellBeing(10)
                        .Build()
    );

    return MoveTemp(Actions);
}
