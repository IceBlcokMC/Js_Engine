#include "api/ServerAPI.h"
#include "APIHelper.h"
#include "api/APIHelper.h"
#include "api/LoggerAPI.h"
#include "api/PlayerAPI.h"
#include "api/command/CommandSenderAPI.h"
#include "endstone/server.h"


namespace jse {

ClassDefine<ServerAPI> ServerAPI::builder =
    defineClass<ServerAPI>("Server")
        .constructor(nullptr)
        .instanceFunction("toString", &ServerAPI::toString)
        .instanceFunction("getName", &ServerAPI::getName)
        .instanceFunction("getVersion", &ServerAPI::getVersion)
        .instanceFunction("getMinecraftVersion", &ServerAPI::getMinecraftVersion)
        .instanceFunction("getLogger", &ServerAPI::getLogger)
        .instanceFunction("getLanguage", &ServerAPI::getLanguage)
        .instanceFunction("getPluginManager", &ServerAPI::getPluginManager)
        .instanceFunction("getPluginCommand", &ServerAPI::getPluginCommand)
        .instanceFunction("getCommandSender", &ServerAPI::getCommandSender)
        .instanceFunction("dispatchCommand", &ServerAPI::dispatchCommand)
        .instanceFunction("getScheduler", &ServerAPI::getScheduler)
        .instanceFunction("getLevel", &ServerAPI::getLevel)
        .instanceFunction("getOnlinePlayers", &ServerAPI::getOnlinePlayers)
        .instanceFunction("getMaxPlayers", &ServerAPI::getMaxPlayers)
        .instanceFunction("setMaxPlayers", &ServerAPI::setMaxPlayers)
        .instanceFunction("getPlayer", &ServerAPI::getPlayer)
        .instanceFunction("getOnlineMode", &ServerAPI::getOnlineMode)
        .instanceFunction("shutdown", &ServerAPI::shutdown)
        .instanceFunction("reload", &ServerAPI::reload)
        .instanceFunction("reloadData", &ServerAPI::reloadData)
        .instanceFunction("broadcast", &ServerAPI::broadcast)
        .instanceFunction("broadcastMessage", &ServerAPI::broadcastMessage)
        .instanceFunction("isPrimaryThread", &ServerAPI::isPrimaryThread)
        .instanceFunction("getScoreboard", &ServerAPI::getScoreboard)
        .instanceFunction("createScoreboard", &ServerAPI::createScoreboard)
        .instanceFunction("getCurrentMillisecondsPerTick", &ServerAPI::getCurrentMillisecondsPerTick)
        .instanceFunction("getAverageMillisecondsPerTick", &ServerAPI::getAverageMillisecondsPerTick)
        .instanceFunction("getCurrentTicksPerSecond", &ServerAPI::getCurrentTicksPerSecond)
        .instanceFunction("getAverageTicksPerSecond", &ServerAPI::getAverageTicksPerSecond)
        .instanceFunction("getCurrentTickUsage", &ServerAPI::getCurrentTickUsage)
        .instanceFunction("getAverageTickUsage", &ServerAPI::getAverageTickUsage)
        .instanceFunction("getStartTime", &ServerAPI::getStartTime)
        .instanceFunction("createBossBar", &ServerAPI::createBossBar)
        .instanceFunction("createBlockData", &ServerAPI::createBlockData)
        .instanceFunction("getBanList", &ServerAPI::getBanList)
        .instanceFunction("getIpBanList", &ServerAPI::getIpBanList)
        .property("BroadcastChannelAdmin", []() { return ConvertToScriptX(endstone::Server::BroadcastChannelAdmin); })
        .property("BroadcastChannelUser", []() { return ConvertToScriptX(endstone::Server::BroadcastChannelUser); })
        .build();

Local<Value> ServerAPI::toString(Arguments const& args) { return ConvertToScriptX("<Server>"); }

Local<Value> ServerAPI::getName(Arguments const& args) { return ConvertToScriptX(get()->getName()); }

Local<Value> ServerAPI::getVersion(Arguments const& args) { return ConvertToScriptX(get()->getVersion()); }

Local<Value> ServerAPI::getMinecraftVersion(Arguments const& args) {
    return ConvertToScriptX(get()->getMinecraftVersion());
}

Local<Value> ServerAPI::getLogger(Arguments const& args) { return Local<Value>(); }

Local<Value> ServerAPI::getLanguage(Arguments const& args) { return Local<Value>(); }

Local<Value> ServerAPI::getPluginManager(Arguments const& args) { return Local<Value>(); }

Local<Value> ServerAPI::getPluginCommand(Arguments const& args) { return Local<Value>(); }

Local<Value> ServerAPI::getCommandSender(Arguments const& args) { return Local<Value>(); }

Local<Value> ServerAPI::dispatchCommand(Arguments const& args) try {
    CheckArgsCount(args, 2);
    CheckArgType(args[0], ValueKind::kObject);
    CheckArgType(args[1], ValueKind::kString);
    return ConvertToScriptX(get()->dispatchCommand(
        *GetScriptClass(CommandSenderAPI, args[0])->get(),
        ConvertFromScriptX<std::string>(args[1])
    ));
}
Catch;

Local<Value> ServerAPI::getScheduler(Arguments const& args) { return Local<Value>(); }

Local<Value> ServerAPI::getLevel(Arguments const& args) { return Local<Value>(); }

Local<Value> ServerAPI::getOnlinePlayers(Arguments const& args) {
    auto result = Array::newArray();
    for (auto* player : get()->getOnlinePlayers()) {
        result.add(PlayerAPI::newPlayerAPI(player));
    }
    return result;
}

Local<Value> ServerAPI::getMaxPlayers(Arguments const& args) { return ConvertToScriptX(get()->getMaxPlayers()); }

Local<Value> ServerAPI::setMaxPlayers(Arguments const& args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kNumber);
    get()->setMaxPlayers(ConvertFromScriptX<int>(args[0]));
    return Local<Value>();
}

Local<Value> ServerAPI::getPlayer(Arguments const& args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kString);
    auto* player = get()->getPlayer(ConvertFromScriptX<std::string>(args[0]));
    return player ? PlayerAPI::newPlayerAPI(player) : Local<Value>();
}

Local<Value> ServerAPI::getOnlineMode(Arguments const& args) { return ConvertToScriptX(get()->getOnlineMode()); }

Local<Value> ServerAPI::shutdown(Arguments const& args) {
    get()->shutdown();
    return Local<Value>();
}

Local<Value> ServerAPI::reload(Arguments const& args) {
    get()->reload();
    return Local<Value>();
}

Local<Value> ServerAPI::reloadData(Arguments const& args) {
    get()->reloadData();
    return Local<Value>();
}

Local<Value> ServerAPI::broadcast(Arguments const& args) {
    CheckArgsCount(args, 2);
    CheckArgType(args[0], ValueKind::kString);
    CheckArgType(args[1], ValueKind::kString);
    get()->broadcast(ConvertFromScriptX<std::string>(args[0]), ConvertFromScriptX<std::string>(args[1]));
    return Local<Value>();
}

Local<Value> ServerAPI::broadcastMessage(Arguments const& args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kString);
    get()->broadcastMessage(ConvertFromScriptX<std::string>(args[0]));
    return Local<Value>();
}

Local<Value> ServerAPI::isPrimaryThread(Arguments const& args) { return ConvertToScriptX(get()->isPrimaryThread()); }

Local<Value> ServerAPI::getScoreboard(Arguments const& args) { return Local<Value>(); }

Local<Value> ServerAPI::createScoreboard(Arguments const& args) { return Local<Value>(); }

Local<Value> ServerAPI::getCurrentMillisecondsPerTick(Arguments const& args) {
    return ConvertToScriptX(get()->getCurrentMillisecondsPerTick());
}

Local<Value> ServerAPI::getAverageMillisecondsPerTick(Arguments const& args) {
    return ConvertToScriptX(get()->getAverageMillisecondsPerTick());
}

Local<Value> ServerAPI::getCurrentTicksPerSecond(Arguments const& args) {
    return ConvertToScriptX(get()->getCurrentTicksPerSecond());
}

Local<Value> ServerAPI::getAverageTicksPerSecond(Arguments const& args) {
    return ConvertToScriptX(get()->getAverageTicksPerSecond());
}

Local<Value> ServerAPI::getCurrentTickUsage(Arguments const& args) {
    return ConvertToScriptX(get()->getCurrentTickUsage());
}

Local<Value> ServerAPI::getAverageTickUsage(Arguments const& args) {
    return ConvertToScriptX(get()->getAverageTickUsage());
}

Local<Value> ServerAPI::getStartTime(Arguments const& args) {
    return ConvertToScriptX(get()->getStartTime().time_since_epoch().count());
}

Local<Value> ServerAPI::createBossBar(Arguments const& args) { return Local<Value>(); }

Local<Value> ServerAPI::createBlockData(Arguments const& args) { return Local<Value>(); }

Local<Value> ServerAPI::getBanList(Arguments const& args) { return Local<Value>(); }

Local<Value> ServerAPI::getIpBanList(Arguments const& args) { return Local<Value>(); }

} // namespace jse