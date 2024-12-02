#pragma once
#include "Using.h"

#include "API/EndStoneAPI.h"
#include "API/LoggerAPI.h"


namespace jse {

inline void BindAPI(ScriptEngine* engine) {
    engine->registerNativeClass(EndStoneAPIClass);
    engine->registerNativeClass(LoggerAPIClass);

    engine->eval(R"()");
}

} // namespace jse
