#include "api/plugin/PluginAPI.h"
#include "api/APIHelper.h"
#include "api/LoggerAPI.h"
#include "api/ServerAPI.h"
#include "api/plugin/PluginDescriptionAPI.h"
#include "endstone/plugin/plugin_description.h"
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
    Local<Value> PluginAPI::FUNC_NAME(Arguments const& /* args */) {                                                   \
        try {                                                                                                          \
            __VA_ARGS__;                                                                                               \
        }                                                                                                              \
        Catch;                                                                                                         \
    }

PLUGINAPI_MACRO(toString, return String::newString("<Plugin>"));

PLUGINAPI_MACRO(
    getDescription,
    return PluginDescriptionAPI::newPluginDescriptionAPI(
        &const_cast<endstone::PluginDescription&>(get()->getDescription())
    )
);

PLUGINAPI_MACRO(onLoad, get()->onLoad(); return Local<Value>());

PLUGINAPI_MACRO(onEnable, get()->onEnable(); return Local<Value>());

PLUGINAPI_MACRO(onDisable, get()->onDisable(); return Local<Value>());

PLUGINAPI_MACRO(getLogger, return LoggerAPI::newLoggerAPI(&get()->getLogger()));

PLUGINAPI_MACRO(isEnabled, return Boolean::newBoolean(get()->isEnabled()));

PLUGINAPI_MACRO(getPluginLoader, return Local<Value>()); // TODO: PluginLoader

PLUGINAPI_MACRO(getServer, return ServerAPI::newServerAPI(&get()->getServer()));

PLUGINAPI_MACRO(getName, return String::newString(get()->getName()));

PLUGINAPI_MACRO(getCommand, return Local<Value>()); // TODO: PluginCommand

PLUGINAPI_MACRO(getDataFolder, return String::newString(get()->getDataFolder().string()));

PLUGINAPI_MACRO(registerEvent, return Local<Value>()); // TODO: implement registerEvent

#undef PLUGINAPI_MACRO

} // namespace jse