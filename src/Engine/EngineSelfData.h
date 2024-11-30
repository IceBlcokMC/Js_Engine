#pragma once
#include <unordered_map>
#include "Using.h"

#include <endstone/logger.h>

namespace jse
{

    struct EngineSelfData
    {
        int mEngineId;
        string mPluginName;
    };
    using EngineSelfDataPtr = std::shared_ptr<EngineSelfData>;

}
