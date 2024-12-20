#pragma once
#include "Utils/Using.h"
#include <unordered_map>


namespace jse {


class EngineManager final {
public:
    EngineManager()                                = default;
    EngineManager(const EngineManager&)            = delete;
    EngineManager& operator=(const EngineManager&) = delete;

    std::unordered_map<EngineID, ScriptEngine*> mEngines;

public:
    static EngineManager& getInstance();

    bool hasEngine(EngineID engineId);

    bool destroyEngine(EngineID engineId);

    ScriptEngine* getEngine(EngineID engineId);

    ScriptEngine* createEngine();
};


} // namespace jse
