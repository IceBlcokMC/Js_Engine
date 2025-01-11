#include "MobAPI.h"
#include "API/APIHelper.h"
#include "APIHelper.h"
#include "Utils/Convert.h"
#include "Utils/Using.h"
#include <cstddef>
#include <sstream>

namespace jse {

ClassDefine<MobAPI> MobAPI::builder =
    defineClass<MobAPI>("Mob")
        .constructor(nullptr)

        .instanceFunction("toString", &MobAPI::toString)
        .instanceFunction("isGliding", &MobAPI::isGliding)

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

        // parent class
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


Local<Value> MobAPI::toString(Arguments const& args) { return ConvertToScriptX("<Mob>"); }

Local<Value> MobAPI::isGliding(Arguments const& args) { return ConvertToScriptX(get()->isGliding()); }

} // namespace jse