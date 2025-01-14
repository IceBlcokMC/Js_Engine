#include "api/command/CommandAPI.h"
#include "api/APIHelper.h"
#include "api/command/CommandSenderAPI.h"
#include "utils/Convert.h"
#include "utils/Defines.h"
#include "utils/Using.h"
#include <endstone/command/command.h>

namespace jse {

ClassDefine<CommandAPI> CommandAPI::builder =
    defineClass<CommandAPI>("Command")
        .constructor(nullptr)
        .instanceFunction("toString", &CommandAPI::toString)
        .instanceFunction("execute", &CommandAPI::execute)
        .instanceFunction("getName", &CommandAPI::getName)
        .instanceFunction("setName", &CommandAPI::setName)
        .instanceFunction("getDescription", &CommandAPI::getDescription)
        .instanceFunction("setDescription", &CommandAPI::setDescription)
        .instanceFunction("getAliases", &CommandAPI::getAliases)
        .instanceFunction("setAliases", &CommandAPI::setAliases)
        .instanceFunction("getUsages", &CommandAPI::getUsages)
        .instanceFunction("setUsages", &CommandAPI::setUsages)
        .instanceFunction("getPermissions", &CommandAPI::getPermissions)
        .instanceFunction("setPermissions", &CommandAPI::setPermissions)
        .instanceFunction("testPermission", &CommandAPI::testPermission)
        .instanceFunction("testPermissionSilently", &CommandAPI::testPermissionSilently)
        .instanceFunction("registerTo", &CommandAPI::registerTo)
        .instanceFunction("unregisterFrom", &CommandAPI::unregisterFrom)
        .instanceFunction("isRegistered", &CommandAPI::isRegistered)
        .instanceFunction("asPluginCommand", &CommandAPI::asPluginCommand)
        .build();


Local<Value> CommandAPI::toString(Arguments const& /* args */) { return ConvertToScriptX("<Command>"); }

Local<Value> CommandAPI::execute(Arguments const& args) {
    CheckArgsCount(args, 2);
    CheckArgType(args[1], ValueKind::kArray);
    try {
        if (!IsInstanceOf<CommandSenderAPI>(args[0])) {
            throw script::Exception("Invalid argument 0: expected CommandSenderAPI");
        }
        return ConvertToScriptX(this->mCommand->execute(
            *GetScriptClass(CommandSenderAPI, args[0])->get(),
            ConvertFromScriptX<std::vector<string>>(args[1])
        ));
    }
    Catch;
}

Local<Value> CommandAPI::getName(Arguments const& /* args */) {
    try {
        return ConvertToScriptX(this->mCommand->getName());
    }
    Catch;
}

Local<Value> CommandAPI::setName(Arguments const& args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kString);
    try {
        this->mCommand->setName(ConvertFromScriptX<string>(args[0]));
        return Local<Value>();
    }
    Catch;
}

Local<Value> CommandAPI::getDescription(Arguments const& /* args */) {
    try {
        return ConvertToScriptX(this->mCommand->getDescription());
    }
    Catch;
}

Local<Value> CommandAPI::setDescription(Arguments const& args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kString);
    try {
        this->mCommand->setDescription(ConvertFromScriptX<string>(args[0]));
        return Local<Value>();
    }
    Catch;
}

Local<Value> CommandAPI::getAliases(Arguments const& /* args */) {
    try {
        return ConvertToScriptX(this->mCommand->getAliases());
    }
    Catch;
}

Local<Value> CommandAPI::setAliases(Arguments const& args) {
    // ...args 不限参数，但每个参数都必须是字符串
    try {
        this->mCommand->setAliases(ConvertFromScriptXArgs<string>(args));
        return Local<Value>();
    }
    Catch;
}

Local<Value> CommandAPI::getUsages(Arguments const& /* args */) {
    try {
        return ConvertToScriptX(this->mCommand->getUsages());
    }
    Catch;
}

Local<Value> CommandAPI::setUsages(Arguments const& args) {
    // ...args 不限参数，但每个参数都必须是字符串
    try {
        this->mCommand->setUsages(ConvertFromScriptXArgs<string>(args));
        return Local<Value>();
    }
    Catch;
}

Local<Value> CommandAPI::getPermissions(Arguments const& /* args */) {
    try {
        return ConvertToScriptX(this->mCommand->getPermissions());
    }
    Catch;
}

Local<Value> CommandAPI::setPermissions(Arguments const& args) {
    // ...args 不限参数，但每个参数都必须是字符串
    try {
        this->mCommand->setPermissions(ConvertFromScriptXArgs<string>(args));
        return Local<Value>();
    }
    Catch;
}

Local<Value> CommandAPI::testPermission(Arguments const& args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kObject);
    try {
        if (!IsInstanceOf<CommandSenderAPI>(args[0])) {
            throw script::Exception("Invalid argument 0: expected CommandSenderAPI");
        }
        return ConvertToScriptX(this->mCommand->testPermission(*GetScriptClass(CommandSenderAPI, args[0])->get()));
    }
    Catch;
}

Local<Value> CommandAPI::testPermissionSilently(Arguments const& args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kObject);
    try {
        if (!IsInstanceOf<CommandSenderAPI>(args[0])) {
            throw script::Exception("Invalid argument 0: expected CommandSenderAPI");
        }
        return ConvertToScriptX(this->mCommand->testPermissionSilently(*GetScriptClass(CommandSenderAPI, args[0])->get()
        ));
    }
    Catch;
}

Local<Value> CommandAPI::registerTo(Arguments const& /* args */) {
    try {
        // TODO: CommandMap
    }
    Catch;
}

Local<Value> CommandAPI::unregisterFrom(Arguments const& /* args */) {
    try {
        // TODO: CommandMap
    }
    Catch;
}

Local<Value> CommandAPI::isRegistered(Arguments const& /* args */) {
    try {
        return ConvertToScriptX(this->mCommand->isRegistered());
    }
    Catch;
}

Local<Value> CommandAPI::asPluginCommand(Arguments const& /* args */) {
    try {
        // TODO: PluginCommand
    }
    Catch;
}


} // namespace jse