#pragma once
#include "Utils/Defines.h"
#include "Utils/Using.h"


namespace jse {


class PluginDescriptionAPI : public ScriptClass {
public:
    explicit PluginDescriptionAPI() : ScriptClass(ScriptClass::ConstructFromCpp<PluginDescriptionAPI>{}) {}

    static Local<Object> newPluginDescriptionAPI() { return (new PluginDescriptionAPI())->getScriptObject(); }

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
};

extern ClassDefine<PluginDescriptionAPI> PluginDescriptionAPIClass;


} // namespace jse