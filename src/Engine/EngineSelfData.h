#pragma once
#include "Using.h"
#include <unordered_map>


#include "endstone/plugin/plugin.h"

namespace jse {

struct EngineSelfData {
    int               mEngineId{-1};
    string            mPluginName{""};
    string            mPluginVersion{"0.0.0"};
    string            mPluginDescription{""};
    string            mFileName{""}; // 入口文件名
    endstone::Plugin* mPlugin{nullptr};
};
using EngineSelfDataPtr = std::shared_ptr<EngineSelfData>;

} // namespace jse
