#include "Loader/JavaScriptPlugin.h"
#include "API/APIHelper.h"
#include "API/Command/CommandAPI.h"
#include "API/Command/CommandSenderAPI.h"
#include "Entry.h"
#include "Manager/EngineData.h"
#include "Manager/NodeManager.h"
#include "Utils/Convert.h"
#include "Utils/Using.h"
#include <endstone/command/command.h>
#include <endstone/logger.h>
#include <iostream>

namespace jse {


JavaScriptPlugin::~JavaScriptPlugin() {
    NodeManager::getInstance().destroyEngine(this->engineId_);
#ifdef DEBUG
    std::cout << "JavaScriptPlugin::~JavaScriptPlugin()  Plugin: " << this->getName() << std::endl;
#endif
}

void JavaScriptPlugin::onLoad() {
    auto        engine = NodeManager::getInstance().getEngine(this->engineId_);
    EngineScope scope(engine->mEngine);
    try {
        ENGINE_DATA()->callOnLoad();
    }
    CatchNotReturn;
}

void JavaScriptPlugin::onEnable() {
    auto        engine = NodeManager::getInstance().getEngine(this->engineId_);
    EngineScope scope(engine->mEngine);
    try {
        ENGINE_DATA()->callOnEnable();
    }
    CatchNotReturn;
}

void JavaScriptPlugin::onDisable() {
    auto        engine = NodeManager::getInstance().getEngine(this->engineId_);
    EngineScope scope(engine->mEngine);
    try {
        ENGINE_DATA()->callOnDisable();
    }
    CatchNotReturn;
}

bool JavaScriptPlugin::onCommand(
    endstone::CommandSender&        sender,
    const endstone::Command&        command,
    const std::vector<std::string>& args
) {
    auto        engine = NodeManager::getInstance().getEngine(this->engineId_);
    EngineScope scope(engine->mEngine);
    try {
        auto data = ENGINE_DATA();
        auto obj  = data->mRegisterInfo.get();
        if (obj.has("onCommand")) {
            auto func = obj.get("onCommand");
            if (func.isFunction()) {
                return func.asFunction()
                    .call(
                        {},
                        CommandSenderAPI::newCommandSenderAPI(&sender),
                        CommandAPI::newCommandAPI(const_cast<endstone::Command*>(&command)), // dangerous?
                        ConvertToScriptX(args)
                    )
                    .asBoolean()
                    .value();
            }
        }
        Entry::getInstance()->getLogger().error("Plugin '{}' does not register onCommand function", data->mFileName);
    }
    CatchNotReturn;
    return true;
}

endstone::PluginDescription const& JavaScriptPlugin::getDescription() const { return this->description_; }


} // namespace jse