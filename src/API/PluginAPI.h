#pragma once
#include "Engine/Using.h"

namespace jse {


class PluginAPI : public ScriptClass {
public:
    explicit PluginAPI() : ScriptClass(ScriptClass::ConstructFromCpp<PluginAPI>{}) {}

    static Local<Object> newPluginAPI() { return (new PluginAPI())->getScriptObject(); }

public:
    Local<Value> toString(Arguments const& args);

    Local<Value> getDescription(Arguments const& args);

    Local<Value> onLoad(Arguments const& args);

    Local<Value> onEnable(Arguments const& args);

    Local<Value> onDisable(Arguments const& args);

    Local<Value> getLogger(Arguments const& args);

    Local<Value> isEnabled(Arguments const& args);

    Local<Value> getPluginLoader(Arguments const& args);

    Local<Value> getServer(Arguments const& args);

    Local<Value> getName(Arguments const& args);

    Local<Value> getCommand(Arguments const& args);

    Local<Value> getDataFolder(Arguments const& args);

    Local<Value> registerEvent(Arguments const& args);
};

extern ClassDefine<PluginAPI> PluginAPIClass;


} // namespace jse