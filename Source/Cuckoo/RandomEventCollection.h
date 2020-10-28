#pragma once

#include "Containers/Array.h"
#include "DataStructures/RandomEvent.h"

namespace Cuckoo
{
    class FRandomEventCollection
    {
    public:
        TArray<FRandomEvent*> Create();
    };
}
