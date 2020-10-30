#include "RandomEventCollection.h"

TArray<Cuckoo::FRandomEvent*> Cuckoo::FRandomEventCollection::Create()
{
    TArray<FRandomEvent*> Events;

    Events.Add(
        FRandomEventBuilder().ShowResultText(FText::FromString(TEXT(
                                 "Весь день повсюду мерещатся заговоры. Плохо, когда у телевизора всего один канал.")))
                             .CheckPrecondition(EStateKey::BelievesInPropaganda)
                             .RemoveState(EStateKey::BelievesInPropaganda)
                             .SetDeltaWellBeing(-7)
                             .Build()
    );

    Events.Add(
        FRandomEventBuilder().ShowResultText(FText::FromString(TEXT(
                                 "Любимый сериал закрыли после пары сезонов. За что? А чем история-то заканчивается?")))
                             .CheckPrecondition(EStateKey::HasFavoriteSeries)
                             .AddState(EStateKey::FavoriteSeriesClosed)
                             .SetDeltaWellBeing(-10)
                             .Build()
    );

    Events.Add(
        FRandomEventBuilder().ShowResultText(FText::FromString(TEXT(
                                 "Актеры из любимого сериала объявили о воссоединении и выходе нового сезона!")))
                             .CheckPrecondition(EStateKey::FavoriteSeriesClosed)
                             .RemoveState(EStateKey::FavoriteSeriesClosed)
                             .SetDeltaWellBeing(5)
                             .Build()
    );

    Events.Add(
        FRandomEventBuilder().ShowResultText(FText::FromString(TEXT(
                                 "Досмотрела сериал, ужасная концовка. Им нужно было закрываться на пару сезонов раньше.")))
                             .CheckPrecondition(EStateKey::HasPremiumStreamingSubscription)
                             .SetDeltaWellBeing(10)
                             .Build()
    );

    Events.Add(
        FRandomEventBuilder().ShowResultText(FText::FromString(TEXT(
                                 "Анонсировали продолжение для любимой игры, но оно является эксклюзивом другой платформы. Так не честно!")))
                             .CheckPrecondition(EStateKey::HasFavoriteGame)
                             .SetDeltaWellBeing(-10)
                             .Build()
    );

    Events.Add(
        FRandomEventBuilder().ShowResultText(FText::FromString(TEXT(
                                 "Заказала еду на обед с доставкой. Позвонил курьер, сказал, что будет на час позже, так как перепутал улицу.")))
                             .SetDeltaWellBeing(-5)
                             .Build()
    );

    Events.Add(
        FRandomEventBuilder().ShowResultText(FText::FromString(TEXT(
                                 "Заказала еду на обед с доставкой. Перепутали заказ, привезли детский завтрак. Веганский.")))
                             .SetDeltaWellBeing(-5)
                             .Build()
    );

    Events.Add(
        FRandomEventBuilder().ShowResultText(FText::FromString(TEXT(
                                 "Любимая бургерная закрылась. Что же теперь заказывать по пятницам?")))
                             .SetDeltaWellBeing(-5)
                             .Build()
    );

    Events.Add(
        FRandomEventBuilder().ShowResultText(FText::FromString(TEXT(
                                 "Заказчик на работе требует исправить дизайн. Говорит, что должно быть сделано уже сейчас.")))
                             .SetDeltaWellBeing(-5)
                             .Build()
    );

    Events.Add(
        FRandomEventBuilder().ShowResultText(FText::FromString(TEXT(
                                 "Компьютер сегодня что-то совсем тормозит. Работать почти невозможно.")))
                             .SetDeltaWellBeing(-5)
                             .Build()
    );

    Events.Add(
        FRandomEventBuilder().ShowResultText(FText::FromString(TEXT(
                                 "Компьютер завис, не сохранив работу. Придётся переделывать.")))
                             .SetDeltaWellBeing(-5)
                             .Build()
    );

    Events.Add(
        FRandomEventBuilder().ShowResultText(FText::FromString(TEXT(
                                 "Видео-совещание с коллегами при ужасной связи. Бесит!")))
                             .CheckPrecondition(EStateKey::HasBadInternet)
                             .AddState(EStateKey::NeedsBetterInternet)
                             .SetDeltaWellBeing(-5)
                             .Build()
    );

    Events.Add(
        FRandomEventBuilder().ShowResultText(FText::FromString(TEXT(
                                 "Новый запрос в друзья в соцсетях. Какой-то спаммер.")))
                             .SetDeltaWellBeing(-5)
                             .Build()
    );

    Events.Add(
        FRandomEventBuilder().ShowResultText(FText::FromString(TEXT(
                                 "В соцсетях много фото с шашлыков. Осуждаю!")))
                             .SetDeltaWellBeing(-5)
                             .Build()
    );

    Events.Add(
        FRandomEventBuilder().ShowResultText(FText::FromString(TEXT(
                                 "Кто-то звонил с незнакомого номера и сказал, что моя банковская карта в опасности. Очень вежливые люди, обещали помочь, сказала им пароль от личного кабинета.")))
                             .SetDeltaWellBeing(-5)
                             .Build()
    );

    Events.Add(
        FRandomEventBuilder().ShowResultText(FText::FromString(TEXT(
                                 "В квартире бардак. Нужно убираться почаще.")))
                             .SetDeltaWellBeing(-5)
                             .Build()
    );

    Events.Add(
        FRandomEventBuilder().ShowResultText(FText::FromString(TEXT(
                                 "Кофе закончился. Как теперь работать?")))
                             .SetDeltaWellBeing(-5)
                             .Build()
    );

    Events.Add(
        FRandomEventBuilder().ShowResultText(FText::FromString(TEXT(
                                 "Мне кажется или я потолстела?")))
                             .SetDeltaWellBeing(-5)
                             .Build()
    );

    Events.Add(
        FRandomEventBuilder().ShowResultText(FText::FromString(TEXT(
                                 "Кто-то поставил минус моему посту в блоге. Обидно!")))
                             .CheckPrecondition(EStateKey::HasBlog)
                             .SetDeltaWellBeing(-5)
                             .Build()
    );

    Events.Add(
        FRandomEventBuilder().ShowResultText(FText::FromString(TEXT(
                                 "Постоянно пишут в комментариях, что я выбрала не ту консоль и вообще дура. Кто-то даже мемы про это делает. Обидно!")))
                             .CheckPrecondition(EStateKey::ConsoleWarrior)
                             .SetDeltaWellBeing(-10)
                             .Build()
    );

    Events.Add(
        FRandomEventBuilder().ShowResultText(FText::FromString(TEXT(
                                 "Один из котов погрыз кабель от телевизора. Пришлось заказывать новый.")))
                             .CheckPrecondition(EStateKey::HasThreePets)
                             .SetDeltaWellBeing(-10)
                             .Build()
    );

    Events.Add(
        FRandomEventBuilder().ShowResultText(FText::FromString(TEXT(
                                 "Кто-то отписался от блога.")))
                             .CheckPrecondition(EStateKey::HasBlog)
                             .SetDeltaWellBeing(-5)
                             .Build()
    );

    Events.Add(
        FRandomEventBuilder().ShowResultText(FText::FromString(TEXT(
                                 "Выложила фото своих успехов в хобби. В комментариях напомнили, что у меня неправильная игровая консоль.")))
                             .CheckPrecondition(EStateKey::HasHobby)
                             .CheckPrecondition(EStateKey::ConsoleWarrior)
                             .SetDeltaWellBeing(-5)
                             .Build()
    );

    return Events;
}
