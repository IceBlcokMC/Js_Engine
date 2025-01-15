#pragma once
#include "utils/Defines.h"
#include "utils/Using.h"

namespace endstone {
class PluginDescription;
}

namespace jse {

class PluginDescriptionAPI : public ScriptClass {
    endstone::PluginDescription* mPluginDescription;

public:
    explicit PluginDescriptionAPI(endstone::PluginDescription* pluginDescription)
    : ScriptClass(ScriptClass::ConstructFromCpp<PluginDescriptionAPI>{}),
      mPluginDescription(pluginDescription) {}

    static Local<Object> newPluginDescriptionAPI(endstone::PluginDescription* pluginDescription) {
        return (new PluginDescriptionAPI(pluginDescription))->getScriptObject();
    }

    endstone::PluginDescription* get() { return mPluginDescription; }

public:
    METHODS(toString);

    METHODS(getName);

    METHODS(getVersion);

    METHODS(getFullName);

    METHODS(getAPIVersion);

    METHODS(getDescription);

    METHODS(getLoad);

    METHODS(getAuthors);

    METHODS(getContributors);

    METHODS(getWebsite);

    METHODS(getPrefix);

    METHODS(getProvides);

    METHODS(getDepend);

    METHODS(getSoftDepend);

    METHODS(getLoadBefore);

    METHODS(getDefaultPermission);

    METHODS(getCommands);

    METHODS(getPermissions);


    static ClassDefine<PluginDescriptionAPI> builder;
};


} // namespace jse