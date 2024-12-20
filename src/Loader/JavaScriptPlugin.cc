#include "JavaScriptPlugin.h"
#include "API/APIHelper.h"
#include "API/CommandSenderAPI.h"
#include "Engine/EngineData.h"
#include "Engine/EngineManager.h"
#include "Entry.h"
#include "Utils/Using.h"
#include "endstone/logger.h"
#include <iostream>


namespace jse {


JavaScriptPlugin::~JavaScriptPlugin() {
    EngineManager::getInstance().destroyEngine(this->engineId_);
#ifdef DEBUG
    std::cout << "JavaScriptPlugin::~JavaScriptPlugin()  Plugin: " << this->getName() << std::endl;
#endif
}

void JavaScriptPlugin::onLoad() {
    auto        engine = EngineManager::getInstance().getEngine(this->engineId_);
    EngineScope scope(engine);
    try {
        ENGINE_DATA()->callOnLoad();
    }
    CatchNotReturn;
}

void JavaScriptPlugin::onEnable() {
    auto        engine = EngineManager::getInstance().getEngine(this->engineId_);
    EngineScope scope(engine);
    try {
        ENGINE_DATA()->callOnEnable();
    }
    CatchNotReturn;
}

void JavaScriptPlugin::onDisable() {
    auto        engine = EngineManager::getInstance().getEngine(this->engineId_);
    EngineScope scope(engine);
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
    auto        engine = EngineManager::getInstance().getEngine(this->engineId_);
    EngineScope scope(engine);
    try {
        auto data = ENGINE_DATA();
        auto obj  = data->mRegisterInfo.get();
        if (obj.has("onCommand")) {
            auto func = obj.get("onCommand");
            if (func.isFunction()) {
                // TODO: args
                return func.asFunction().call({}, CommandSenderAPI::newCommandSenderAPI(&sender)).asBoolean().value();
            }
        }
        Entry::getInstance()->getLogger().error("Plugin '{}' does not register onCommand function", data->mFileName);
    }
    CatchNotReturn;
    return true;
}

endstone::PluginDescription const& JavaScriptPlugin::getDescription() const { return this->description_; }


} // namespace jse