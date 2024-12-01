#pragma once
#include <unordered_map>
#include "Using.h"

#include <endstone/logger.h>

namespace jse
{

    struct EngineSelfData
    {
        int mEngineId{-1};
        string mPluginName{""};
        string mPluginVersion{"0.0.0"};
        string mPluginDescription{""};
        string mFileName{""}; // 入口文件名
    };
    using EngineSelfDataPtr = std::shared_ptr<EngineSelfData>;

}
