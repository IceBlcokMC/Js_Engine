#include "JavaScriptPlugin.h"
#include "API/APIHelper.h"
#include "Engine/EngineData.h"
#include "Engine/EngineManager.h"
#include "Engine/Using.h"
#include "Entry.h"
#include "endstone/command/console_command_sender.h"
#include "endstone/command/plugin_command.h"
#include "endstone/detail/server.h"
#include "endstone/event/server/server_load_event.h"
#include "endstone/logger.h"
#include "endstone/player.h"
#include "endstone/plugin/plugin_loader.h"
#include "endstone/plugin/plugin_manager.h"
#include "endstone/server.h"
#include "fmt/format.h"
#include <filesystem>
#include <iostream>
#include <utility>


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

endstone::PluginDescription const& JavaScriptPlugin::getDescription() const { return this->description_; }


} // namespace jse