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

Cuckoo::FRandomEventBuilder& Cuckoo::FRandomEventBuilder::CheckPrecondition(EStateKey Precondition)
{
    this->Preconditions.Add(Precondition);
    return *this;
}

Cuckoo::FRandomEventBuilder& Cuckoo::FRandomEventBuilder::RemoveState(EStateKey StateKey)
{
    this->StatesToRemove.Add(StateKey);
    return *this;
}

Cuckoo::FRandomEventBuilder& Cuckoo::FRandomEventBuilder::AddState(EStateKey StateKey)
{
    this->StatesToAdd.Add(StateKey);
    return *this;
}

Cuckoo::FRandomEventBuilder& Cuckoo::FRandomEventBuilder::ShowResultText(const FText& Value)
{
    this->ResultText = Value;
    return *this;
}

Cuckoo::FRandomEvent* Cuckoo::FRandomEventBuilder::Build()
{
    FRandomEvent* Event = new FRandomEvent();
    Event->Preconditions = MoveTemp(this->Preconditions);
    Event->StatesToRemove = MoveTemp(this->StatesToRemove);
    Event->StatesToAdd = MoveTemp(this->StatesToAdd);
    Event->ResultText = MoveTemp(this->ResultText);
    return Event;
}
