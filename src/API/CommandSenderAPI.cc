#include "CommandSenderAPI.h"
#include "ActorAPI.h"
#include "PlayerAPI.h"
#include "API/APIHelper.h"
#include "Utils/Convert.h"
#include "Utils/Using.h"
#include <cstddef>
#include <sstream>


namespace jse {

ClassDefine<CommandSenderAPI> CommandSenderAPI::builder =
    defineClass<CommandSenderAPI>("CommandSender")
        .constructor(nullptr)
        .instanceFunction("toString", &CommandSenderAPI::toString)
        .instanceFunction("asCommandSender", &CommandSenderAPI::asCommandSender)
        .instanceFunction("asConsole", &CommandSenderAPI::asConsole)
        .instanceFunction("asActor", &CommandSenderAPI::asActor)
        .instanceFunction("asPlayer", &CommandSenderAPI::asPlayer)
        .instanceFunction("sendMessage", &CommandSenderAPI::sendMessage)
        .instanceFunction("sendErrorMessage", &CommandSenderAPI::sendErrorMessage)
        .instanceFunction("getServer", &CommandSenderAPI::getServer)
        .instanceFunction("getName", &CommandSenderAPI::getName)

        // parent class
        // .instanceFunction("toString", &PermissibleAPI::toString)
        .instanceFunction("isOp", &PermissibleAPI::isOP)
        .instanceFunction("setOp", &PermissibleAPI::setOp)
        .instanceFunction("isPermissionSet", &PermissibleAPI::isPermissionSet)
        .instanceFunction("hasPermission", &PermissibleAPI::hasPermission)
        .instanceFunction("addAttachment", &PermissibleAPI::addAttachment)
        .instanceFunction("removeAttachment", &PermissibleAPI::removeAttachment)
        .instanceFunction("recalculatePermissions", &PermissibleAPI::recalculatePermissions)
        .instanceFunction("getEffectivePermissions", &PermissibleAPI::getEffectivePermissions)
        // .instanceFunction("asCommandSender", &PermissibleAPI::getEffectivePermissions)

        .build();


Local<Value> CommandSenderAPI::toString(Arguments const& args) { return ConvertToScriptX("<CommandSender>"); }

// Local<Value> CommandSenderAPI::asCommandSender(Arguments const& args) {}

Local<Value> CommandSenderAPI::asConsole(Arguments const& args) { return Local<Value>(); }

Local<Value> CommandSenderAPI::asActor(Arguments const& args) {
    if (mSender->asActor() == nullptr) return Local<Value>();
    return ActorAPI::newActorAPI(mSender->asActor());
}

Local<Value> CommandSenderAPI::asPlayer(Arguments const& args) {
    if (mSender->asPlayer() == nullptr) return Local<Value>();
    return PlayerAPI::newPlayerAPI(mSender->asPlayer());
}

Local<Value> CommandSenderAPI::sendMessage(Arguments const& args) {
    try {
        std::ostringstream oss;
        for (size_t i = 0; i < args.size(); ++i) ToString(args[i], oss);
        this->mSender->sendMessage(oss.str());
        return Local<Value>();
    }
    Catch;
}

Local<Value> CommandSenderAPI::sendErrorMessage(Arguments const& args) {
    try {
        std::ostringstream oss;
        for (size_t i = 0; i < args.size(); ++i) ToString(args[i], oss);
        this->mSender->sendErrorMessage(oss.str());
        return Local<Value>();
    }
    Catch;
}

Local<Value> CommandSenderAPI::getServer(Arguments const& args) { return Local<Value>(); }

Local<Value> CommandSenderAPI::getName(Arguments const& args) {
    try {
        return ConvertToScriptX(this->mSender->getName());
    }
    Catch;
}


} // namespace jse