#include "EngineManager.h"
#include "BindAPI.h"
#include "EngineData.h"

namespace jse {
EngineManager& EngineManager::getInstance() {
    static EngineManager instance;
    return instance;
}

bool EngineManager::hasEngine(EngineID engineId) { return this->mEngines.contains(engineId); }

bool EngineManager::destroyEngine(EngineID engineId) {
    if (!this->hasEngine(engineId)) {
        return false;
    }

    auto engine = this->mEngines[engineId];
    engine->destroy(); // 销毁引擎

    this->mEngines.erase(engineId);
    return true;
}

ScriptEngine* EngineManager::getEngine(EngineID engineId) {
    if (!this->hasEngine(engineId)) {
        return nullptr;
    }

    return this->mEngines[engineId];
}

ScriptEngine* EngineManager::createEngine() {
    static EngineID __NextEngineId = 0;
    EngineID const  engineId       = __NextEngineId++;

    auto engine              = new ScriptEngineImpl();
    this->mEngines[engineId] = engine;

    EngineScope scope(engine);                               // 进入引擎作用域
    BindAPI(engine);                                         // 绑定API
    engine->setData(std::make_shared<EngineData>(engineId)); // 设置引擎自身数据

    return engine;
}
} // namespace jse
