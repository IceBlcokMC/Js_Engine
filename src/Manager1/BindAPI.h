#pragma once
#include "API/Actor/ActorAPI.h"
#include "API/Actor/MobAPI.h"
#include "API/Command/CommandAPI.h"
#include "API/Command/CommandSenderAPI.h"
#include "API/JSE/EnumAPI.h"
#include "API/JSE/FileAPI.h"
#include "API/JSE/JSEAPI.h"
#include "API/LoggerAPI.h"
#include "API/JSE/PluginAPI.h"
#include "API/JSE/PluginDescriptionAPI.h"
#include "API/Permissions/PermissibleAPI.h"
#include "API/PlayerAPI.h"
#include "Utils/Using.h"

namespace jse {

inline void BindAPI(ScriptEngine* engine) {

    // enum class
    EnumAPI::RegisterEnum(engine);

    // static class
    engine->registerNativeClass(JSEAPI::builder);

    // instance class
    engine->registerNativeClass<PluginAPI>(PluginAPI::builder);
    engine->registerNativeClass<FileAPI>(FileAPI::builder);
    engine->registerNativeClass<LoggerAPI>(LoggerAPI::builder);
    engine->registerNativeClass<PluginDescriptionAPI>(PluginDescriptionAPI::builder);
    engine->registerNativeClass<PermissibleAPI>(PermissibleAPI::builder);
    engine->registerNativeClass<CommandSenderAPI>(CommandSenderAPI::builder);
    engine->registerNativeClass<CommandAPI>(CommandAPI::builder);
    engine->registerNativeClass<ActorAPI>(ActorAPI::builder);
    engine->registerNativeClass<MobAPI>(MobAPI::builder);
    engine->registerNativeClass<PlayerAPI>(PlayerAPI::builder);
}


} // namespace jse
