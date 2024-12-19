#include "PluginAPI.h"
#include "API/LoggerAPI.h"
#include "API/PluginDescription.h"
#include "APIHelper.h"
#include "Engine/EngineData.h"
#include "Engine/Using.h"
#include <cstddef>


namespace jse {

ClassDefine<PluginAPI> PluginAPIClass = defineClass<PluginAPI>("Plugin")
                                            .constructor(nullptr)
                                            .instanceFunction("toString", &PluginAPI::toString)
                                            .instanceFunction("getDescription", &PluginAPI::getDescription)
                                            .instanceFunction("onLoad", &PluginAPI::onLoad)
                                            .instanceFunction("onEnable", &PluginAPI::onEnable)
                                            .instanceFunction("onDisable", &PluginAPI::onDisable)
                                            .instanceFunction("getLogger", &PluginAPI::getLogger)
                                            .instanceFunction("isEnabled", &PluginAPI::isEnabled)
                                            .instanceFunction("getPluginLoader", &PluginAPI::getPluginLoader)
                                            .instanceFunction("getServer", &PluginAPI::getServer)
                                            .instanceFunction("getName", &PluginAPI::getName)
                                            .instanceFunction("getCommand", &PluginAPI::getCommand)
                                            .instanceFunction("getDataFolder", &PluginAPI::getDataFolder)
                                            .instanceFunction("registerEvent", &PluginAPI::registerEvent)
                                            .build();


#define PLUGINAPI_MACRO(FUNC_NAME, ...)                                                                                \
    Local<Value> PluginAPI::FUNC_NAME(Arguments const& args) {                                                         \
        try {                                                                                                          \
            __VA_ARGS__;                                                                                               \
        }                                                                                                              \
        Catch;                                                                                                         \
    }

PLUGINAPI_MACRO(toString, return String::newString("<Plugin>"));

PLUGINAPI_MACRO(getDescription, return PluginDescriptionAPI::newPluginDescriptionAPI());

PLUGINAPI_MACRO(onLoad, ENGINE_DATA()->callOnLoad(); return Local<Value>());

PLUGINAPI_MACRO(onEnable, ENGINE_DATA()->callOnEnable(); return Local<Value>());

PLUGINAPI_MACRO(onDisable, ENGINE_DATA()->callOnDisable(); return Local<Value>());

PLUGINAPI_MACRO(getLogger, return LoggerAPI::newLoggerAPI());

PLUGINAPI_MACRO(isEnabled, return Boolean::newBoolean(ENGINE_DATA()->mPlugin->isEnabled()));

PLUGINAPI_MACRO(getPluginLoader, return Local<Value>()); // todo

PLUGINAPI_MACRO(getServer, return Local<Value>()); // todo

PLUGINAPI_MACRO(getName, return String::newString(ENGINE_DATA()->mPlugin->getName()));

PLUGINAPI_MACRO(getCommand, return Local<Value>()); // todo

PLUGINAPI_MACRO(getDataFolder, return String::newString(ENGINE_DATA()->mPlugin->getDataFolder().string()));

PLUGINAPI_MACRO(registerEvent, return Local<Value>()); // todo

#undef PLUGINAPI_MACRO

} // namespace jse