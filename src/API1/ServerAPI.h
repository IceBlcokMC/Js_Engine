#pragma once
#include "Utils/Defines.h"
#include "Utils/Using.h"
#include <endstone/server.h>

namespace jse {

class ServerAPI : public ScriptClass {
    endstone::Server* mServer;

public:
    explicit ServerAPI(endstone::Server* server)
    : mServer(server),
      ScriptClass(ScriptClass::ConstructFromCpp<ServerAPI>{}) {}

    static Local<Object> newServerAPI(endstone::Server* server) { return (new ServerAPI(server))->getScriptObject(); }

    endstone::Server* get() { return mServer; }

public:
    METHODS(toString);
    METHODS(getName);
    METHODS(getVersion);
    METHODS(getMinecraftVersion);
    METHODS(getLogger); // todo
    METHODS(getLanguage); // todo
    METHODS(getPluginManager); // todo
    METHODS(getPluginCommand); // todo
    METHODS(getCommandSender); // todo
    METHODS(dispatchCommand);
    METHODS(getScheduler); // todo
    METHODS(getLevel); // todo
    METHODS(getOnlinePlayers);
    METHODS(getMaxPlayers);
    METHODS(setMaxPlayers);
    METHODS(getPlayer); // todo uuid无法获取
    METHODS(getOnlineMode);
    METHODS(shutdown);
    METHODS(reload);
    METHODS(reloadData);
    METHODS(broadcast);
    METHODS(broadcastMessage);
    METHODS(isPrimaryThread);
    METHODS(getScoreboard); // todo
    METHODS(createScoreboard); // todo
    METHODS(getCurrentMillisecondsPerTick);
    METHODS(getAverageMillisecondsPerTick);
    METHODS(getCurrentTicksPerSecond);
    METHODS(getAverageTicksPerSecond);
    METHODS(getCurrentTickUsage);
    METHODS(getAverageTickUsage);
    METHODS(getStartTime);
    METHODS(createBossBar);   // todo
    METHODS(createBlockData); // todo
    METHODS(getBanList);      // todo
    METHODS(getIpBanList);    // todo

    static ClassDefine<ServerAPI> builder;
};


} // namespace jse