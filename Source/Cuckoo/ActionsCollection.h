#pragma once

#include "Containers/Array.h"
#include "DataStructures/Action.h"

namespace Cuckoo
{
    class FActionsCollection
    {
    public:
        TArray<FAction*> Create();
    };
}
