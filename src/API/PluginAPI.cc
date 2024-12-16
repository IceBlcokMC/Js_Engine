#include "PluginAPI.h"
#include "API/LoggerAPI.h"
#include "APIHelper.h"
#include "Engine/EngineData.h"
#include "Engine/Using.h"
#include <cstddef>


namespace jse {

ClassDefine<PluginAPI> PluginAPIClass = defineClass<PluginAPI>("Plugin")
                                            .constructor(nullptr)
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


Local<Value> PluginAPI::getDescription(Arguments const& args) { return Local<Value>(); }

Local<Value> PluginAPI::onLoad(Arguments const& args) {
    try {
        ENGINE_DATA()->callOnLoad();
        return Local<Value>();
    }
    Catch;
}

Local<Value> PluginAPI::onEnable(Arguments const& args) {
    try {
        ENGINE_DATA()->callOnEnable();
        return Local<Value>();
    }
    Catch;
}

Local<Value> PluginAPI::onDisable(Arguments const& args) {
    try {
        ENGINE_DATA()->callOnDisable();
        return Local<Value>();
    }
    Catch;
}

Local<Value> PluginAPI::getLogger(Arguments const& args) {
    try {
        return LoggerAPI::newLoggerAPI();
    }
    Catch;
}

Local<Value> PluginAPI::isEnabled(Arguments const& args) {
    try {
        return Boolean::newBoolean(ENGINE_DATA()->mPlugin->isEnabled());
    }
    Catch;
}

Local<Value> PluginAPI::getPluginLoader(Arguments const& args) { return Local<Value>(); }

Local<Value> PluginAPI::getServer(Arguments const& args) { return Local<Value>(); }

Local<Value> PluginAPI::getName(Arguments const& args) {
    try {
        return String::newString(ENGINE_DATA()->mPlugin->getName());
    }
    Catch;
}

Local<Value> PluginAPI::getCommand(Arguments const& args) { return Local<Value>(); }

Local<Value> PluginAPI::getDataFolder(Arguments const& args) {
    try {
        return String::newString(ENGINE_DATA()->mPlugin->getDataFolder().string());
    }
    Catch;
}

Local<Value> PluginAPI::registerEvent(Arguments const& args) { return Local<Value>(); }


} // namespace jse