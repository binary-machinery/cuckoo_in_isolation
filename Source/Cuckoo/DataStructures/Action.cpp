#include "Action.h"


const TArray<Cuckoo::EStateKey>& Cuckoo::FAction::GetPreconditions()
{
    return Preconditions;
}

const TArray<Cuckoo::EStateKey>& Cuckoo::FAction::GetStatesToRemove()
{
    return StatesToRemove;
}

const TArray<Cuckoo::EStateKey>& Cuckoo::FAction::GetStatesToAdd()
{
    return StatesToAdd;
}

const FText& Cuckoo::FAction::GetMenuText()
{
    return MenuText;
}

const FText& Cuckoo::FAction::GetResultText()
{
    return ResultText;
}

// Builder =====================================================================================

Cuckoo::FActionBuilder& Cuckoo::FActionBuilder::AddPrecondition(EStateKey Precondition)
{
    Preconditions.Add(Precondition);
    return *this;
}

Cuckoo::FActionBuilder& Cuckoo::FActionBuilder::AddStatesToRemove(EStateKey StateKey)
{
    StatesToRemove.Add(StateKey);
    return *this;
}

Cuckoo::FActionBuilder& Cuckoo::FActionBuilder::AddStatesToAdd(EStateKey StateKey)
{
    StatesToAdd.Add(StateKey);
    return *this;
}

Cuckoo::FActionBuilder& Cuckoo::FActionBuilder::SetMenuText(const FText& Value)
{
    this->MenuText = Value;
    return *this;
}

Cuckoo::FActionBuilder& Cuckoo::FActionBuilder::SetResultText(const FText& Value)
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
