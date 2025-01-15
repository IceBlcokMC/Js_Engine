#pragma once
#include "utils/Defines.h"
#include "utils/Using.h"

namespace jse {


class PluginAPI : public ScriptClass {
public:
    explicit PluginAPI() : ScriptClass(ScriptClass::ConstructFromCpp<PluginAPI>{}) {}

    static Local<Object> newPluginAPI() { return (new PluginAPI())->getScriptObject(); }

public:
    METHODS(toString);

    METHODS(getDescription);

    METHODS(onLoad);

    METHODS(onEnable);

    METHODS(onDisable);

    METHODS(getLogger);

    METHODS(isEnabled);

    METHODS(getPluginLoader);

    METHODS(getServer);

    METHODS(getName);

    METHODS(getCommand);

    METHODS(getDataFolder);

    METHODS(registerEvent);


    static ClassDefine<PluginAPI> builder;
};


} // namespace jse