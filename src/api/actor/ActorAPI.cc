#include "ActorAPI.h"
#include "api/APIHelper.h"
#include "utils/Convert.h"
#include "utils/Using.h"
#include <cstddef>
#include <sstream>


namespace jse {

ClassDefine<ActorAPI> ActorAPI::builder =
    defineClass<ActorAPI>("Actor")
        .constructor(nullptr)

        .instanceFunction("toString", &ActorAPI::toString)
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


Local<Value> ActorAPI::toString(Arguments const& /* args */) { return ConvertToScriptX("<Actor>"); }

Local<Value> ActorAPI::getType(Arguments const& /* args */) { return ConvertToScriptX(get()->getType()); }

Local<Value> ActorAPI::getRuntimeId(Arguments const& /* args */) {
    return ConvertToScriptX(static_cast<int64_t>(get()->getRuntimeId()));
}

Local<Value> ActorAPI::getLocation(Arguments const& /* args */) { return Local<Value>(); }

Local<Value> ActorAPI::getVelocity(Arguments const& /* args */) { return Local<Value>(); }

Local<Value> ActorAPI::isOnGround(Arguments const& /* args */) { return ConvertToScriptX(get()->isOnGround()); }

Local<Value> ActorAPI::isInWater(Arguments const& /* args */) { return ConvertToScriptX(get()->isInWater()); }

Local<Value> ActorAPI::isInLava(Arguments const& /* args */) { return ConvertToScriptX(get()->isInLava()); }

Local<Value> ActorAPI::getLevel(Arguments const& /* args */) { return Local<Value>(); }

Local<Value> ActorAPI::getDimension(Arguments const& /* args */) { return Local<Value>(); }

Local<Value> ActorAPI::setRotation(Arguments const& /* args */) { return Local<Value>(); }

Local<Value> ActorAPI::teleport(Arguments const& /* args */) { return Local<Value>(); }

Local<Value> ActorAPI::getId(Arguments const& /* args */) { return ConvertToScriptX(get()->getId()); }

Local<Value> ActorAPI::isDead(Arguments const& /* args */) { return ConvertToScriptX(get()->isDead()); }

Local<Value> ActorAPI::getHealth(Arguments const& /* args */) { return ConvertToScriptX(get()->getHealth()); }

Local<Value> ActorAPI::setHealth(Arguments const& args) try {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kNumber);
    get()->setHealth(args[0].asNumber().toInt32()).value();
    return Local<Value>();
}
Catch;

Local<Value> ActorAPI::getMaxHealth(Arguments const& /* args */) { return ConvertToScriptX(get()->getMaxHealth()); }

Local<Value> ActorAPI::getScoreboardTags(Arguments const& /* args */) { return ConvertToScriptX(get()->getScoreboardTags()); }

Local<Value> ActorAPI::addScoreboardTag(Arguments const& args) try {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kString);
    return ConvertToScriptX(get()->addScoreboardTag(args[0].asString().toString()));
}
Catch;

Local<Value> ActorAPI::removeScoreboardTag(Arguments const& args) try {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kString);
    return ConvertToScriptX(get()->removeScoreboardTag(args[0].asString().toString()));
}
Catch;

Local<Value> ActorAPI::isNameTagVisible(Arguments const& /* args */) { return ConvertToScriptX(get()->isNameTagVisible()); }

Local<Value> ActorAPI::setNameTagVisible(Arguments const& args) try {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kBoolean);
    get()->setNameTagVisible(args[0].asBoolean().value());
    return Local<Value>();
}
Catch;

Local<Value> ActorAPI::isNameTagAlwaysVisible(Arguments const& /* args */) {
    return ConvertToScriptX(get()->isNameTagAlwaysVisible());
}

Local<Value> ActorAPI::setNameTagAlwaysVisible(Arguments const& args) try {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kBoolean);
    get()->setNameTagAlwaysVisible(args[0].asBoolean().value());
    return Local<Value>();
}
Catch;

Local<Value> ActorAPI::getNameTag(Arguments const& /* args */) { return String::newString(get()->getNameTag()); }

Local<Value> ActorAPI::setNameTag(Arguments const& args) try {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kString);
    get()->setNameTag(args[0].asString().toString());
    return Local<Value>();
}
Catch;

Local<Value> ActorAPI::getScoreTag(Arguments const& /* args */) { return String::newString(get()->getScoreTag()); }

Local<Value> ActorAPI::setScoreTag(Arguments const& args) try {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kString);
    get()->setScoreTag(args[0].asString().toString());
    return Local<Value>();
}
Catch;

} // namespace jse