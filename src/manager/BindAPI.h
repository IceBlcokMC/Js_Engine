#pragma once
#include "api/LoggerAPI.h"
#include "api/PlayerAPI.h"
#include "api/actor/ActorAPI.h"
#include "api/actor/MobAPI.h"
#include "api/command/CommandAPI.h"
#include "api/command/CommandSenderAPI.h"
#include "api/jse/EnumAPI.h"
#include "api/jse/FileAPI.h"
#include "api/jse/JSEAPI.h"
#include "api/permissions/PermissibleAPI.h"
#include "api/permissions/PermissionAPI.h"
#include "api/plugin/PluginAPI.h"
#include "api/plugin/PluginDescriptionAPI.h"
#include "utils/Using.h"


namespace jse {

inline void BindAPI(ScriptEngine* engine) {

    // enum class
    EnumAPI::RegisterEnum(engine);

    // static class
    engine->registerNativeClass(JSEAPI::builder);
    engine->registerNativeClass<FileAPI>(FileAPI::builder);

    // instance class
    engine->registerNativeClass<PluginAPI>(PluginAPI::builder);
    engine->registerNativeClass<PluginDescriptionAPI>(PluginDescriptionAPI::builder);

    engine->registerNativeClass<PermissibleAPI>(PermissibleAPI::builder);
    engine->registerNativeClass<PermissionAPI>(PermissionAPI::builder);

    engine->registerNativeClass<CommandAPI>(CommandAPI::builder);
    engine->registerNativeClass<CommandSenderAPI>(CommandSenderAPI::builder);

    engine->registerNativeClass<ActorAPI>(ActorAPI::builder);
    engine->registerNativeClass<MobAPI>(MobAPI::builder);

    engine->registerNativeClass<LoggerAPI>(LoggerAPI::builder);
    engine->registerNativeClass<PlayerAPI>(PlayerAPI::builder);
}


} // namespace jse
