#include "API/PlayerAPI.h"
#include "API/APIHelper.h"
#include "APIHelper.h"
#include "Utils/Convert.h"
#include "Utils/Using.h"

namespace jse {

ClassDefine<PlayerAPI> PlayerAPI::builder =
    defineClass<PlayerAPI>("Player")
        .constructor(nullptr)

        .instanceFunction("toString", &PlayerAPI::toString)
        .instanceFunction("getUniqueId", &PlayerAPI::getUniqueId)
        .instanceFunction("getXuid", &PlayerAPI::getXuid)
        .instanceFunction("getAddress", &PlayerAPI::getAddress)
        .instanceFunction("sendPopup", &PlayerAPI::sendPopup)
        .instanceFunction("sendTip", &PlayerAPI::sendTip)
        .instanceFunction("sendToast", &PlayerAPI::sendToast)
        .instanceFunction("kick", &PlayerAPI::kick)
        .instanceFunction("giveExp", &PlayerAPI::giveExp)
        .instanceFunction("giveExpLevels", &PlayerAPI::giveExpLevels)
        .instanceFunction("getExpProgress", &PlayerAPI::getExpProgress)
        .instanceFunction("setExpProgress", &PlayerAPI::setExpProgress)
        .instanceFunction("getExpLevel", &PlayerAPI::getExpLevel)
        .instanceFunction("setExpLevel", &PlayerAPI::setExpLevel)
        .instanceFunction("getTotalExp", &PlayerAPI::getTotalExp)
        .instanceFunction("getAllowFlight", &PlayerAPI::getAllowFlight)
        .instanceFunction("setAllowFlight", &PlayerAPI::setAllowFlight)
        .instanceFunction("isFlying", &PlayerAPI::isFlying)
        .instanceFunction("setFlying", &PlayerAPI::setFlying)
        .instanceFunction("getFlySpeed", &PlayerAPI::getFlySpeed)
        .instanceFunction("setFlySpeed", &PlayerAPI::setFlySpeed)
        .instanceFunction("getWalkSpeed", &PlayerAPI::getWalkSpeed)
        .instanceFunction("setWalkSpeed", &PlayerAPI::setWalkSpeed)
        .instanceFunction("getScoreboard", &PlayerAPI::getScoreboard)
        .instanceFunction("setScoreboard", &PlayerAPI::setScoreboard)
        .instanceFunction("sendTitle", &PlayerAPI::sendTitle)
        .instanceFunction("resetTitle", &PlayerAPI::resetTitle)
        .instanceFunction("spawnParticle", &PlayerAPI::spawnParticle)
        .instanceFunction("getPing", &PlayerAPI::getPing)
        .instanceFunction("updateCommands", &PlayerAPI::updateCommands)
        .instanceFunction("performCommand", &PlayerAPI::performCommand)
        .instanceFunction("getGameMode", &PlayerAPI::getGameMode)
        .instanceFunction("setGameMode", &PlayerAPI::setGameMode)
        .instanceFunction("getInventory", &PlayerAPI::getInventory)
        .instanceFunction("getLocale", &PlayerAPI::getLocale)
        .instanceFunction("getDeviceOS", &PlayerAPI::getDeviceOS)
        .instanceFunction("getDeviceId", &PlayerAPI::getDeviceId)
        .instanceFunction("getGameVersion", &PlayerAPI::getGameVersion)
        .instanceFunction("getSkin", &PlayerAPI::getSkin)
        .instanceFunction("transfer", &PlayerAPI::transfer)
        .instanceFunction("sendForm", &PlayerAPI::sendForm)
        .instanceFunction("closeForm", &PlayerAPI::closeForm)
        .instanceFunction("sendPacket", &PlayerAPI::sendPacket)

        // parent class
        .instanceFunction("getType", &ActorAPI::getType)
        .instanceFunction("getRuntimeId", &ActorAPI::getRuntimeId)
        .instanceFunction("getLocation", &ActorAPI::getLocation)
        .instanceFunction("getVelocity", &ActorAPI::getVelocity)
        .instanceFunction("isOnGround", &ActorAPI::isOnGround)
        .instanceFunction("isInWater", &ActorAPI::isInWater)
        .instanceFunction("isInLava", &ActorAPI::isInLava)
        .instanceFunction("getLevel", &ActorAPI::getLevel)
        .instanceFunction("getDimension", &ActorAPI::getDimension)
        .instanceFunction("setRotation", &ActorAPI::setRotation)
        .instanceFunction("teleport", &ActorAPI::teleport)
        .instanceFunction("getId", &ActorAPI::getId)
        .instanceFunction("isDead", &ActorAPI::isDead)
        .instanceFunction("getHealth", &ActorAPI::getHealth)
        .instanceFunction("getMaxHealth", &ActorAPI::getMaxHealth)
        .instanceFunction("getScoreboardTags", &ActorAPI::getScoreboardTags)
        .instanceFunction("addScoreboardTag", &ActorAPI::addScoreboardTag)
        .instanceFunction("removeScoreboardTag", &ActorAPI::removeScoreboardTag)
        .instanceFunction("isNameTagVisible", &ActorAPI::isNameTagVisible)
        .instanceFunction("setNameTagVisible", &ActorAPI::setNameTagVisible)
        .instanceFunction("isNameTagAlwaysVisible", &ActorAPI::isNameTagAlwaysVisible)
        .instanceFunction("setNameTagAlwaysVisible", &ActorAPI::setNameTagAlwaysVisible)
        .instanceFunction("getNameTag", &ActorAPI::getNameTag)
        .instanceFunction("setNameTag", &ActorAPI::setNameTag)
        .instanceFunction("getScoreTag", &ActorAPI::getScoreTag)
        .instanceFunction("setScoreTag", &ActorAPI::setScoreTag)

        .instanceFunction("asCommandSender", &CommandSenderAPI::asCommandSender)
        .instanceFunction("asConsole", &CommandSenderAPI::asConsole)
        .instanceFunction("asActor", &CommandSenderAPI::asActor)
        .instanceFunction("asPlayer", &CommandSenderAPI::asPlayer)
        .instanceFunction("sendMessage", &CommandSenderAPI::sendMessage)
        .instanceFunction("sendErrorMessage", &CommandSenderAPI::sendErrorMessage)
        .instanceFunction("getServer", &CommandSenderAPI::getServer)
        .instanceFunction("getName", &CommandSenderAPI::getName)

        .instanceFunction("isOp", &PermissibleAPI::isOP)
        .instanceFunction("setOp", &PermissibleAPI::setOp)
        .instanceFunction("isPermissionSet", &PermissibleAPI::isPermissionSet)
        .instanceFunction("hasPermission", &PermissibleAPI::hasPermission)
        .instanceFunction("addAttachment", &PermissibleAPI::addAttachment)
        .instanceFunction("removeAttachment", &PermissibleAPI::removeAttachment)
        .instanceFunction("recalculatePermissions", &PermissibleAPI::recalculatePermissions)
        .instanceFunction("getEffectivePermissions", &PermissibleAPI::getEffectivePermissions)

        .build();


Local<Value> PlayerAPI::toString(Arguments const& args) { return ConvertToScriptX("<Player>"); }

Local<Value> PlayerAPI::getUniqueId(Arguments const& args) { return ConvertToScriptX(get()->getUniqueId().str()); }

Local<Value> PlayerAPI::getXuid(Arguments const& args) { return ConvertToScriptX(get()->getXuid()); }

Local<Value> PlayerAPI::getAddress(Arguments const& args) {
    auto result  = Object::newObject();
    auto address = get()->getAddress();
    result.set("host", ConvertToScriptX(address.getHostname()));
    result.set("port", ConvertToScriptX(address.getPort()));
    return result;
}

Local<Value> PlayerAPI::sendPopup(Arguments const& args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kString);
    get()->sendPopup(args[0].asString().toString());
    return Local<Value>();
}

Local<Value> PlayerAPI::sendTip(Arguments const& args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kString);
    get()->sendTip(args[0].asString().toString());
    return Local<Value>();
}

Local<Value> PlayerAPI::sendToast(Arguments const& args) {
    CheckArgsCount(args, 2);
    CheckArgType(args[0], ValueKind::kString);
    CheckArgType(args[0], ValueKind::kString);
    get()->sendToast(args[0].asString().toString(), args[1].asString().toString());
    return Local<Value>();
}

Local<Value> PlayerAPI::kick(Arguments const& args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kString);
    get()->kick(args[0].asString().toString());
    return Local<Value>();
}

Local<Value> PlayerAPI::giveExp(Arguments const& args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kNumber);
    get()->giveExp(args[0].asNumber().toInt64());
    return Local<Value>();
}

Local<Value> PlayerAPI::giveExpLevels(Arguments const& args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kNumber);
    get()->giveExpLevels(args[0].asNumber().toInt64());
    return Local<Value>();
}

Local<Value> PlayerAPI::getExpProgress(Arguments const& args) { return ConvertToScriptX(get()->getExpProgress()); }

Local<Value> PlayerAPI::setExpProgress(Arguments const& args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kNumber);
    get()->setExpProgress(args[0].asNumber().toFloat());
    return Local<Value>();
}

Local<Value> PlayerAPI::getExpLevel(Arguments const& args) { return ConvertToScriptX(get()->getExpLevel()); }

Local<Value> PlayerAPI::setExpLevel(Arguments const& args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kNumber);
    get()->setExpLevel(args[0].asNumber().toInt64());
    return Local<Value>();
}

Local<Value> PlayerAPI::getTotalExp(Arguments const& args) { return ConvertToScriptX(get()->getTotalExp()); }

Local<Value> PlayerAPI::getAllowFlight(Arguments const& args) { return ConvertToScriptX(get()->getAllowFlight()); }

Local<Value> PlayerAPI::setAllowFlight(Arguments const& args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kBoolean);
    get()->setAllowFlight(args[0].asBoolean().value());
    return Local<Value>();
}

Local<Value> PlayerAPI::isFlying(Arguments const& args) { return ConvertToScriptX(get()->isFlying()); }

Local<Value> PlayerAPI::setFlying(Arguments const& args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kBoolean);
    get()->setFlying(args[0].asBoolean().value());
    return Local<Value>();
}

Local<Value> PlayerAPI::getFlySpeed(Arguments const& args) { return ConvertToScriptX(get()->getFlySpeed()); }

Local<Value> PlayerAPI::setFlySpeed(Arguments const& args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kNumber);
    get()->setFlySpeed(args[0].asNumber().toFloat());
    return Local<Value>();
}

Local<Value> PlayerAPI::getWalkSpeed(Arguments const& args) { return ConvertToScriptX(get()->getWalkSpeed()); }

Local<Value> PlayerAPI::setWalkSpeed(Arguments const& args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kNumber);
    get()->setWalkSpeed(args[0].asNumber().toFloat());
    return Local<Value>();
}

Local<Value> PlayerAPI::getScoreboard(Arguments const& args) { return Local<Value>(); }

Local<Value> PlayerAPI::setScoreboard(Arguments const& args) { return Local<Value>(); }

Local<Value> PlayerAPI::sendTitle(Arguments const& args) {
    CheckArgsCount(args, 2);
    CheckArgType(args[0], ValueKind::kString);
    CheckArgType(args[1], ValueKind::kString);
    if (args.size() > 2) {
        CheckArgsCount(args, 5);
        CheckArgType(args[2], ValueKind::kNumber);
        CheckArgType(args[3], ValueKind::kNumber);
        CheckArgType(args[4], ValueKind::kNumber);
    }
    if (args.size() == 2) {
        get()->sendTitle(args[0].asString().toString(), args[1].asString().toString());
    } else {
        get()->sendTitle(
            args[0].asString().toString(),
            args[1].asString().toString(),
            args[2].asNumber().toInt64(),
            args[3].asNumber().toInt64(),
            args[4].asNumber().toInt64()
        );
    }
    return Local<Value>();
}

Local<Value> PlayerAPI::resetTitle(Arguments const& args) {
    get()->resetTitle();
    return Local<Value>();
}

Local<Value> PlayerAPI::spawnParticle(Arguments const& args) {
    return Local<Value>();
}

Local<Value> PlayerAPI::getPing(Arguments const& args) { return ConvertToScriptX(get()->getPing().count()); }

Local<Value> PlayerAPI::updateCommands(Arguments const& args) {
    get()->updateCommands();
    return Local<Value>();
}

Local<Value> PlayerAPI::performCommand(Arguments const& args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kString);
    return ConvertToScriptX(get()->performCommand(args[0].asString().toString()));
}

Local<Value> PlayerAPI::getGameMode(Arguments const& args) { return ConvertToScriptX(get()->getGameMode()); }

Local<Value> PlayerAPI::setGameMode(Arguments const& args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kNumber);
    get()->setGameMode(ConvertFromScriptX<endstone::GameMode>(args[0]));
    return Local<Value>();
}

Local<Value> PlayerAPI::getInventory(Arguments const& args) { return Local<Value>(); }

Local<Value> PlayerAPI::getLocale(Arguments const& args) { return ConvertToScriptX(get()->getLocale()); }

Local<Value> PlayerAPI::getDeviceOS(Arguments const& args) { return ConvertToScriptX(get()->getDeviceOS()); }

Local<Value> PlayerAPI::getDeviceId(Arguments const& args) { return ConvertToScriptX(get()->getDeviceId()); }

Local<Value> PlayerAPI::getGameVersion(Arguments const& args) { return ConvertToScriptX(get()->getGameVersion()); }

Local<Value> PlayerAPI::getSkin(Arguments const& args) { return Local<Value>(); }

Local<Value> PlayerAPI::transfer(Arguments const& args) {
    CheckArgsCount(args, 2);
    CheckArgType(args[0], ValueKind::kString);
    CheckArgType(args[1], ValueKind::kNumber);
    get()->transfer(args[0].asString().toString(), args[1].asNumber().toInt64());
    return Local<Value>();
}

Local<Value> PlayerAPI::sendForm(Arguments const& args) { return Local<Value>(); }

Local<Value> PlayerAPI::closeForm(Arguments const& args) { return Local<Value>(); }

Local<Value> PlayerAPI::sendPacket(Arguments const& args) { return Local<Value>(); }

} // namespace jse