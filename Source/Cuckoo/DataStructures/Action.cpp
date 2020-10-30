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

bool Cuckoo::FAction::HasUnlimitedActivations() const
{
    return bUnlimitedActivations;
}

float Cuckoo::FAction::GetDeltaWellBeing() const
{
    return DeltaWellBeing;
}

float Cuckoo::FAction::GetDiminishingReturnModifier() const
{
    return DiminishingReturnModifier;
}

// Builder =====================================================================================

Cuckoo::FActionBuilder::FActionBuilder()
{
    Action = new FAction();
}

Cuckoo::FActionBuilder::~FActionBuilder()
{
    // Memory leak protection if Build() hasn't been called
    if (Action)
    {
        delete Action;
    }
}

Cuckoo::FActionBuilder& Cuckoo::FActionBuilder::CheckPrecondition(EStateKey Precondition)
{
    Action->Preconditions.Add(Precondition);
    return *this;
}

Cuckoo::FActionBuilder& Cuckoo::FActionBuilder::RemoveState(EStateKey StateKey)
{
    Action->StatesToRemove.Add(StateKey);
    return *this;
}

Cuckoo::FActionBuilder& Cuckoo::FActionBuilder::AddStates(EStateKey StateKey)
{
    Action->StatesToAdd.Add(StateKey);
    return *this;
}

Cuckoo::FActionBuilder& Cuckoo::FActionBuilder::ShowMenuText(const FText& MenuText)
{
    Action->MenuText = MenuText;
    return *this;
}

Cuckoo::FActionBuilder& Cuckoo::FActionBuilder::ShowResultText(const FText& ResultText)
{
    Action->ResultText = ResultText;
    return *this;
}

Cuckoo::FActionBuilder& Cuckoo::FActionBuilder::HasUnlimitedActivations(bool Value)
{
    Action->bUnlimitedActivations = Value;
    return *this;
}


Cuckoo::FActionBuilder& Cuckoo::FActionBuilder::SetDeltaWellBeing(float Value)
{
    Action->DeltaWellBeing = Value;
    return *this;
}

Cuckoo::FActionBuilder& Cuckoo::FActionBuilder::SetDiminishingReturnModifier(float Value)
{
    Action->DiminishingReturnModifier = Value;
    return *this;
}

Cuckoo::FAction* Cuckoo::FActionBuilder::Build()
{
    FAction* Result = Action;
    Action = nullptr;
    return Result;
}
