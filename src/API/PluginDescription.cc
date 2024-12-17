#include "PluginDescription.h"
#include "API/APIHelper.h"
#include "API/Convert.h"
#include "Engine/EngineData.h"
#include "Engine/Using.h"


namespace jse {

ClassDefine<PluginDescriptionAPI> PluginDescriptionAPIClass =
    defineClass<PluginDescriptionAPI>("PluginDescription")
        .constructor(nullptr)
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


Local<Value> PluginDescriptionAPI::getName(Arguments const& args) {
    try {
        return ConvertToScript(ENGINE_DATA()->mPlugin->getDescription().getName());
    }
    Catch;
}

Local<Value> PluginDescriptionAPI::getVersion(Arguments const& args) {
    try {
        return ConvertToScript(ENGINE_DATA()->mPlugin->getDescription().getVersion());
    }
    Catch;
}

Local<Value> PluginDescriptionAPI::getFullName(Arguments const& args) {
    try {
        return ConvertToScript(ENGINE_DATA()->mPlugin->getDescription().getFullName());
    }
    Catch;
}

Local<Value> PluginDescriptionAPI::getAPIVersion(Arguments const& args) {
    try {
        return ConvertToScript(ENGINE_DATA()->mPlugin->getDescription().getAPIVersion());
    }
    Catch;
}

Local<Value> PluginDescriptionAPI::getDescription(Arguments const& args) {
    try {
        return ConvertToScript(ENGINE_DATA()->mPlugin->getDescription().getDescription());
    }
    Catch;
}

Local<Value> PluginDescriptionAPI::getLoad(Arguments const& args) {
    try {
        return ConvertToScript(ENGINE_DATA()->mPlugin->getDescription().getLoad());
    }
    Catch;
}

Local<Value> PluginDescriptionAPI::getAuthors(Arguments const& args) {
    try {
        return ConvertToScript(ENGINE_DATA()->mPlugin->getDescription().getAuthors());
    }
    Catch;
}

Local<Value> PluginDescriptionAPI::getContributors(Arguments const& args) {
    try {
        return ConvertToScript(ENGINE_DATA()->mPlugin->getDescription().getContributors());
    }
    Catch;
}

Local<Value> PluginDescriptionAPI::getWebsite(Arguments const& args) {
    try {
        return ConvertToScript(ENGINE_DATA()->mPlugin->getDescription().getWebsite());
    }
    Catch;
}

Local<Value> PluginDescriptionAPI::getPrefix(Arguments const& args) {
    try {
        return ConvertToScript(ENGINE_DATA()->mPlugin->getDescription().getPrefix());
    }
    Catch;
}

Local<Value> PluginDescriptionAPI::getProvides(Arguments const& args) {
    try {
        return ConvertToScript(ENGINE_DATA()->mPlugin->getDescription().getProvides());
    }
    Catch;
}

Local<Value> PluginDescriptionAPI::getDepend(Arguments const& args) {
    try {
        return ConvertToScript(ENGINE_DATA()->mPlugin->getDescription().getDepend());
    }
    Catch;
}

Local<Value> PluginDescriptionAPI::getSoftDepend(Arguments const& args) {
    try {
        return ConvertToScript(ENGINE_DATA()->mPlugin->getDescription().getSoftDepend());
    }
    Catch;
}

Local<Value> PluginDescriptionAPI::getLoadBefore(Arguments const& args) {
    try {
        return ConvertToScript(ENGINE_DATA()->mPlugin->getDescription().getLoadBefore());
    }
    Catch;
}

Local<Value> PluginDescriptionAPI::getDefaultPermission(Arguments const& args) {
    try {
        return ConvertToScript(ENGINE_DATA()->mPlugin->getDescription().getDefaultPermission());
    }
    Catch;
}

Local<Value> PluginDescriptionAPI::getCommands(Arguments const& args) { return Local<Value>(); }

Local<Value> PluginDescriptionAPI::getPermissions(Arguments const& args) { return Local<Value>(); }


} // namespace jse