#pragma once
#include "Utils/Using.h"

namespace jse {


class PluginDescriptionAPI : public ScriptClass {
public:
    explicit PluginDescriptionAPI() : ScriptClass(ScriptClass::ConstructFromCpp<PluginDescriptionAPI>{}) {}

    static Local<Object> newPluginDescriptionAPI() { return (new PluginDescriptionAPI())->getScriptObject(); }

public:
    Local<Value> toString(Arguments const& args);

    Local<Value> getName(Arguments const& args);

    Local<Value> getVersion(Arguments const& args);

    Local<Value> getFullName(Arguments const& args);

    Local<Value> getAPIVersion(Arguments const& args);

    Local<Value> getDescription(Arguments const& args);

    Local<Value> getLoad(Arguments const& args);

    Local<Value> getAuthors(Arguments const& args);

    Local<Value> getContributors(Arguments const& args);

    Local<Value> getWebsite(Arguments const& args);

    Local<Value> getPrefix(Arguments const& args);

    Local<Value> getProvides(Arguments const& args);

    Local<Value> getDepend(Arguments const& args);

    Local<Value> getSoftDepend(Arguments const& args);

    Local<Value> getLoadBefore(Arguments const& args);

    Local<Value> getDefaultPermission(Arguments const& args);

    Local<Value> getCommands(Arguments const& args);

    Local<Value> getPermissions(Arguments const& args);
};

extern ClassDefine<PluginDescriptionAPI> PluginDescriptionAPIClass;


} // namespace jse