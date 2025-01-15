#include "api/jse/PluginAPI.h"
#include "api/APIHelper.h"
#include "api/LoggerAPI.h"
#include "api/ServerAPI.h"
#include "api/jse/PluginDescriptionAPI.h"
#include "manager/EngineData.h"
#include "utils/Using.h"



namespace jse {

ClassDefine<PluginAPI> PluginAPI::builder = defineClass<PluginAPI>("Plugin")
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

PLUGINAPI_MACRO(getPluginLoader, return Local<Value>()); // TODO: PluginLoader

PLUGINAPI_MACRO(getServer, return ServerAPI::newServerAPI(&ENGINE_DATA()->mPlugin->getServer()));

PLUGINAPI_MACRO(getName, return String::newString(ENGINE_DATA()->mPlugin->getName()));

PLUGINAPI_MACRO(getCommand, return Local<Value>()); // TODO: PluginCommand

PLUGINAPI_MACRO(getDataFolder, return String::newString(ENGINE_DATA()->mPlugin->getDataFolder().string()));

PLUGINAPI_MACRO(registerEvent, return Local<Value>()); // TODO: implement registerEvent

#undef PLUGINAPI_MACRO

} // namespace jse