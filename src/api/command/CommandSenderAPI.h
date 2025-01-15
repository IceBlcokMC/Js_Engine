#pragma once
#include "api/permissions/PermissibleAPI.h"
#include "utils/Defines.h"
#include "utils/Using.h"
#include <endstone/command/command_sender.h>

namespace jse {

class CommandSenderAPI : public PermissibleAPI {
    endstone::CommandSender* mSender;

public:
    template <typename T>
    explicit CommandSenderAPI(endstone::CommandSender* sender, ScriptClass::ConstructFromCpp<T> tag)
    : PermissibleAPI(sender, tag),
      mSender(sender) {}

    explicit CommandSenderAPI(endstone::CommandSender* sender)
    : PermissibleAPI(sender, ScriptClass::ConstructFromCpp<CommandSenderAPI>{}),
      mSender(sender) {}

    static Local<Object> newCommandSenderAPI(endstone::CommandSender* sender) {
        return (new CommandSenderAPI(sender))->getScriptObject();
    }

    endstone::CommandSender* get() { return mSender; }

    METHODS(toString);
    METHODS(asCommandSender);
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