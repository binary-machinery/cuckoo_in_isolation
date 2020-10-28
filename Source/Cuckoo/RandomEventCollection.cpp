#include "RandomEventCollection.h"

TArray<Cuckoo::FRandomEvent*> Cuckoo::FRandomEventCollection::Create()
{
    TArray<FRandomEvent*> Events;

    Events.Add(
        FRandomEventBuilder().ShowResultText(FText::FromString(TEXT("Весь день повсюду мерещатся заговоры. Плохо, когда у телевизора всего один канал.")))
                             .CheckPrecondition(EStateKey::BelievesInPropaganda)
                             .RemoveState(EStateKey::BelievesInPropaganda)
                             .Build()
    );

    Events.Add(
        FRandomEventBuilder().ShowResultText(FText::FromString(TEXT("Любимый сериал закрыли после пары сезонов. Как так-то? А чем история-то заканчивается?")))
                             .CheckPrecondition(EStateKey::HasFavoriteSeries)
                             .AddState(EStateKey::FavoriteSeriesClosed)
                             .Build()
    );

    Events.Add(
        FRandomEventBuilder().ShowResultText(FText::FromString(TEXT("Актеры из любимого сериала объявили о воссоединении и выходе нового сезона!")))
                             .CheckPrecondition(EStateKey::FavoriteSeriesClosed)
                             .RemoveState(EStateKey::FavoriteSeriesClosed)
                             .Build()
    );

    return Events;
}
