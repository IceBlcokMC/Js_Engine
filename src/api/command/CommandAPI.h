#pragma once
#include "api/APIHelper.h"
#include "utils/Defines.h"
#include "utils/Using.h"
#include <endstone/command/command.h>

namespace jse {

class CommandAPI : public ScriptClass {
    endstone::Command* mCommand;

public:
    CommandAPI(endstone::Command* command)
    : ScriptClass(ScriptClass::ConstructFromCpp<CommandAPI>{}),
      mCommand(command) {}

    static Local<Object> newCommandAPI(endstone::Command* cmd) { return (new CommandAPI(cmd))->getScriptObject(); }

    endstone::Command* get() { return mCommand; }

    METHODS(toString);
    METHODS(execute);
    METHODS(getName);
    METHODS(setName);
    METHODS(getDescription);
    METHODS(setDescription);
    METHODS(getAliases);
    METHODS(setAliases);
    METHODS(getUsages);
    METHODS(setUsages);
    METHODS(getPermissions);
    METHODS(setPermissions);
    METHODS(testPermission);
    METHODS(testPermissionSilently);
    METHODS(registerTo);
    METHODS(unregisterFrom);
    METHODS(isRegistered);
    METHODS(asPluginCommand);


    static ClassDefine<CommandAPI> builder;
};


} // namespace jse