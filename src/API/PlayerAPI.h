#pragma once

#include "API/MobAPI.h"
#include "Utils/Defines.h"
#include "Utils/Using.h"
#include "endstone/player.h"

namespace jse {

class PlayerAPI : public MobAPI {
    endstone::Player* mPlayer;

public:
    template <typename T>
    explicit PlayerAPI(endstone::Player* player, ScriptClass::ConstructFromCpp<T> tag) : MobAPI(player, tag),
                                                                                   mPlayer(player) {}

    explicit PlayerAPI(endstone::Player* player) : MobAPI(player, ScriptClass::ConstructFromCpp<PlayerAPI>{}), mPlayer(player) {}

    static Local<Object> newPlayerAPI(endstone::Player* player) { return (new PlayerAPI(player))->getScriptObject(); }

    endstone::Player* get() { return mPlayer; }

    METHODS(toString);
    METHODS(getUniqueId);
    METHODS(getXuid);
    METHODS(getAddress);
    METHODS(sendPopup);
    METHODS(sendTip);
    METHODS(sendToast);
    METHODS(kick);
    METHODS(giveExp);
    METHODS(giveExpLevels);
    METHODS(getExpProgress);
    METHODS(setExpProgress);
    METHODS(getExpLevel);
    METHODS(setExpLevel);
    METHODS(getTotalExp);
    METHODS(getAllowFlight);
    METHODS(setAllowFlight);
    METHODS(isFlying);
    METHODS(setFlying);
    METHODS(getFlySpeed);
    METHODS(setFlySpeed);
    METHODS(getWalkSpeed);
    METHODS(setWalkSpeed);
    METHODS(getScoreboard); // todo
    METHODS(setScoreboard); // todo
    METHODS(sendTitle);
    METHODS(resetTitle);
    METHODS(spawnParticle); // todo
    METHODS(getPing);
    METHODS(updateCommands);
    METHODS(performCommand);
    METHODS(getGameMode);
    METHODS(setGameMode);
    METHODS(getInventory); // todo
    METHODS(getLocale);
    METHODS(getDeviceOS);
    METHODS(getDeviceId);
    METHODS(getGameVersion);
    METHODS(getSkin); // todo
    METHODS(transfer);
    METHODS(sendForm); // todo
    METHODS(closeForm); // todo
    METHODS(sendPacket); // todo

    static ClassDefine<PlayerAPI> builder;
};


} // namespace jse