#pragma once
#include "API/JSEAPI.h"
#include "API/LoggerAPI.h"
#include "API/PluginAPI.h"
#include "API/PluginDescription.h"
#include "Using.h"


namespace jse {


inline void BindAPI(ScriptEngine* engine) {
    // static class
    engine->registerNativeClass(JSEAPIClass);

    // instance class
    engine->registerNativeClass<PluginAPI>(PluginAPIClass);
    engine->registerNativeClass<LoggerAPI>(LoggerAPIClass);
    engine->registerNativeClass<PluginDescriptionAPI>(PluginDescriptionAPIClass);
}


} // namespace jse
