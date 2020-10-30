#include "RandomEvent.h"

const TArray<Cuckoo::EStateKey>& Cuckoo::FRandomEvent::GetPreconditions() const
{
    return Preconditions;
}

const TArray<Cuckoo::EStateKey>& Cuckoo::FRandomEvent::GetStatesToRemove() const
{
    return StatesToRemove;
}

const TArray<Cuckoo::EStateKey>& Cuckoo::FRandomEvent::GetStatesToAdd() const
{
    return StatesToAdd;
}

const FText& Cuckoo::FRandomEvent::GetResultText() const
{
    return ResultText;
}

float Cuckoo::FRandomEvent::GetDeltaWellBeing() const
{
    return DeltaWellBeing;
}

Cuckoo::FRandomEventBuilder::FRandomEventBuilder()
{
    Event = new FRandomEvent();
}

Cuckoo::FRandomEventBuilder::~FRandomEventBuilder()
{
    // Memory leak protection if Build() hasn't been called
    if (Event)
    {
        delete Event;
    }
}

Cuckoo::FRandomEventBuilder& Cuckoo::FRandomEventBuilder::CheckPrecondition(EStateKey Precondition)
{
    Event->Preconditions.Add(Precondition);
    return *this;
}

Cuckoo::FRandomEventBuilder& Cuckoo::FRandomEventBuilder::RemoveState(EStateKey StateKey)
{
    Event->StatesToRemove.Add(StateKey);
    return *this;
}

Cuckoo::FRandomEventBuilder& Cuckoo::FRandomEventBuilder::AddState(EStateKey StateKey)
{
    Event->StatesToAdd.Add(StateKey);
    return *this;
}

Cuckoo::FRandomEventBuilder& Cuckoo::FRandomEventBuilder::ShowResultText(const FText& Value)
{
    Event->ResultText = Value;
    return *this;
}

Cuckoo::FRandomEventBuilder& Cuckoo::FRandomEventBuilder::SetDeltaWellBeing(float Value)
{
    Event->DeltaWellBeing = Value;
    return *this;
}

Cuckoo::FRandomEvent* Cuckoo::FRandomEventBuilder::Build()
{
    FRandomEvent* Result = Event;
    Event = nullptr;
    return Result;
}
