#pragma once

#include "API/PermissibleAPI.h"
#include "Utils/Defines.h"
#include "Utils/Using.h"
#include "endstone/command/command_sender.h"
namespace jse {


class CommandSenderAPI : public PermissibleAPI {
    endstone::CommandSender* mSender;

public:
    CommandSenderAPI(endstone::CommandSender* sender)
    : PermissibleAPI(sender, ScriptClass::ConstructFromCpp<CommandSenderAPI>{}),
      mSender(sender) {}

    static Local<Object> newCommandSenderAPI(endstone::CommandSender* sender) {
        return (new CommandSenderAPI(sender))->getScriptObject();
    }

    METHODS(toString);
    // METHODS(asCommandSender);
    METHODS(asConsole);
    METHODS(asActor);
    METHODS(asPlayer);
    METHODS(sendMessage);
    METHODS(sendErrorMessage);
    METHODS(getServer);
    METHODS(getName);


    static ClassDefine<CommandSenderAPI> builder;
};


} // namespace jse