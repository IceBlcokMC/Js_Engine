#pragma once
#include "EngineSelfData.h"
#include "Using.h"
#include <unordered_map>


namespace jse {
class EngineManager final {
public:
    EngineManager()                                = default;
    EngineManager(const EngineManager&)            = delete;
    EngineManager& operator=(const EngineManager&) = delete;

    std::unordered_map<int, ScriptEngine*> mEngines;

public:
    static EngineManager&    getInstance();                           // 单例模式
    static EngineSelfDataPtr getEngineSelfData(ScriptEngine* engine); // 获取引擎自身数据

    bool hasEngine(int engineId);

    bool destroyEngine(int engineId);

    ScriptEngine* getEngine(int engineId);

    ScriptEngine* createEngine();
};
} // namespace jse
