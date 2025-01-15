#include "api/jse/PluginDescriptionAPI.h"
#include "api/APIHelper.h"
#include "api/command/CommandAPI.h"
#include "api/permissions/PermissionAPI.h"
#include "manager/EngineData.h"
#include "utils/Convert.h"
#include "utils/Using.h"


namespace jse {

ClassDefine<PluginDescriptionAPI> PluginDescriptionAPI::builder =
    defineClass<PluginDescriptionAPI>("PluginDescription")
        .constructor(nullptr)
        .instanceFunction("toString", &PluginDescriptionAPI::toString)
        .instanceFunction("getName", &PluginDescriptionAPI::getName)
        .instanceFunction("getVersion", &PluginDescriptionAPI::getVersion)
        .instanceFunction("getFullName", &PluginDescriptionAPI::getFullName)
        .instanceFunction("getAPIVersion", &PluginDescriptionAPI::getAPIVersion)
        .instanceFunction("getDescription", &PluginDescriptionAPI::getDescription)
        .instanceFunction("getLoad", &PluginDescriptionAPI::getLoad)
        .instanceFunction("getAuthors", &PluginDescriptionAPI::getAuthors)
        .instanceFunction("getContributors", &PluginDescriptionAPI::getContributors)
        .instanceFunction("getWebsite", &PluginDescriptionAPI::getWebsite)
        .instanceFunction("getPrefix", &PluginDescriptionAPI::getPrefix)
        .instanceFunction("getProvides", &PluginDescriptionAPI::getProvides)
        .instanceFunction("getDepend", &PluginDescriptionAPI::getDepend)
        .instanceFunction("getSoftDepend", &PluginDescriptionAPI::getSoftDepend)
        .instanceFunction("getLoadBefore", &PluginDescriptionAPI::getLoadBefore)
        .instanceFunction("getDefaultPermission", &PluginDescriptionAPI::getDefaultPermission)
        .instanceFunction("getCommands", &PluginDescriptionAPI::getCommands)
        .instanceFunction("getPermissions", &PluginDescriptionAPI::getPermissions)
        .build();

#define PLUGINDESCRIPTIONAPI_MACRO(FUNC_NAME, ...)                                                                     \
    Local<Value> PluginDescriptionAPI::FUNC_NAME(Arguments const& args) {                                              \
        try {                                                                                                          \
            __VA_ARGS__;                                                                                               \
        }                                                                                                              \
        Catch;                                                                                                         \
    }

#define GETDESCRIPTION_MACRO(FUNC_NAME) return ConvertToScriptX(ENGINE_DATA()->mPlugin->getDescription().FUNC_NAME());

PLUGINDESCRIPTIONAPI_MACRO(toString, return String::newString("<PluginDescription>"));

PLUGINDESCRIPTIONAPI_MACRO(getName, GETDESCRIPTION_MACRO(getName));

PLUGINDESCRIPTIONAPI_MACRO(getVersion, GETDESCRIPTION_MACRO(getVersion));

PLUGINDESCRIPTIONAPI_MACRO(getFullName, GETDESCRIPTION_MACRO(getFullName));

PLUGINDESCRIPTIONAPI_MACRO(getAPIVersion, GETDESCRIPTION_MACRO(getAPIVersion));

PLUGINDESCRIPTIONAPI_MACRO(getDescription, GETDESCRIPTION_MACRO(getDescription));

PLUGINDESCRIPTIONAPI_MACRO(getLoad, GETDESCRIPTION_MACRO(getLoad));

PLUGINDESCRIPTIONAPI_MACRO(getAuthors, GETDESCRIPTION_MACRO(getAuthors));

PLUGINDESCRIPTIONAPI_MACRO(getContributors, GETDESCRIPTION_MACRO(getContributors));

PLUGINDESCRIPTIONAPI_MACRO(getWebsite, GETDESCRIPTION_MACRO(getWebsite));

PLUGINDESCRIPTIONAPI_MACRO(getPrefix, GETDESCRIPTION_MACRO(getPrefix));

PLUGINDESCRIPTIONAPI_MACRO(getProvides, GETDESCRIPTION_MACRO(getProvides));

PLUGINDESCRIPTIONAPI_MACRO(getDepend, GETDESCRIPTION_MACRO(getDepend));

PLUGINDESCRIPTIONAPI_MACRO(getSoftDepend, GETDESCRIPTION_MACRO(getSoftDepend));

PLUGINDESCRIPTIONAPI_MACRO(getLoadBefore, GETDESCRIPTION_MACRO(getLoadBefore));

PLUGINDESCRIPTIONAPI_MACRO(getDefaultPermission, GETDESCRIPTION_MACRO(getDefaultPermission));

// PLUGINDESCRIPTIONAPI_MACRO(getCommands, return Local<Value>());
Local<Value> PluginDescriptionAPI::getCommands(Arguments const& args) {
    try {
        auto cmds  = ENGINE_DATA()->mPlugin->getDescription().getCommands();
        auto array = Array::newArray(cmds.size());
        for (auto c : cmds) {
            array.add(CommandAPI::newCommandAPI(&c));
        }
        return array;
    }
    Catch;
}

// PLUGINDESCRIPTIONAPI_MACRO(getPermissions, GETDESCRIPTION_MACRO(getPermissions));
Local<Value> PluginDescriptionAPI::getPermissions(Arguments const& args) {
    try {
        auto perms = ENGINE_DATA()->mPlugin->getDescription().getPermissions();
        auto array = Array::newArray(perms.size());
        for (auto p : perms) {
            array.add(PermissionAPI::newPermissionAPI(&p));
        }
        return array;
    }
    Catch;
}

#undef PLUGINDESCRIPTIONAPI_MACRO
#undef GETDESCRIPTION_MACRO

} // namespace jse