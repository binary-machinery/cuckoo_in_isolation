#include "Action.h"


const TArray<Cuckoo::EStateKey>& Cuckoo::FAction::GetPreconditions() const
{
    return Preconditions;
}

const TArray<Cuckoo::EStateKey>& Cuckoo::FAction::GetStatesToRemove() const
{
    return StatesToRemove;
}

const TArray<Cuckoo::EStateKey>& Cuckoo::FAction::GetStatesToAdd() const
{
    return StatesToAdd;
}

const FText& Cuckoo::FAction::GetMenuText() const
{
    return MenuText;
}

const FText& Cuckoo::FAction::GetResultText() const
{
    return ResultText;
}

// Builder =====================================================================================

Cuckoo::FActionBuilder& Cuckoo::FActionBuilder::CheckPrecondition(EStateKey Precondition)
{
    Preconditions.Add(Precondition);
    return *this;
}

Cuckoo::FActionBuilder& Cuckoo::FActionBuilder::RemoveState(EStateKey StateKey)
{
    StatesToRemove.Add(StateKey);
    return *this;
}

Cuckoo::FActionBuilder& Cuckoo::FActionBuilder::AddStates(EStateKey StateKey)
{
    StatesToAdd.Add(StateKey);
    return *this;
}

Cuckoo::FActionBuilder& Cuckoo::FActionBuilder::ShowMenuText(const FText& Value)
{
    this->MenuText = Value;
    return *this;
}

Cuckoo::FActionBuilder& Cuckoo::FActionBuilder::ShowResultText(const FText& Value)
{
    this->ResultText = Value;
    return *this;
}

Cuckoo::FAction* Cuckoo::FActionBuilder::Build()
{
    FAction* Action = new FAction();
    Action->Preconditions = MoveTemp(this->Preconditions);
    Action->StatesToRemove = MoveTemp(this->StatesToRemove);
    Action->StatesToAdd = MoveTemp(this->StatesToAdd);
    Action->MenuText = MoveTemp(this->MenuText);
    Action->ResultText = MoveTemp(this->ResultText);
    return Action;
}
