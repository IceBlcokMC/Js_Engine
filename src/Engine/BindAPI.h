#pragma once
#include "Using.h"

#include "API/LoggerAPI.h"
#include "API/EndStoneAPI.h"

namespace jse
{

    inline void BindAPI(ScriptEngine *engine)
    {
        engine->registerNativeClass(EndStoneAPIClass);
        engine->registerNativeClass(LoggerAPIClass);
    }

}
