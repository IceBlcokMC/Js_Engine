#pragma once
#include "endstone/plugin/plugin.h"
#include "utils/Defines.h"
#include "utils/Using.h"

namespace jse {


class PluginAPI : public ScriptClass {
    endstone::Plugin* mPlugin;

public:
    explicit PluginAPI(endstone::Plugin* plugin)
    : ScriptClass(ScriptClass::ConstructFromCpp<PluginAPI>{}),
      mPlugin(plugin) {}

    static Local<Object> newPluginAPI(endstone::Plugin* plugin) { return (new PluginAPI(plugin))->getScriptObject(); }

    endstone::Plugin* get() { return mPlugin; }

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