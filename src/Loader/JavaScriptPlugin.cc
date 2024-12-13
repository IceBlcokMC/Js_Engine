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


JavaScriptPlugin::JavaScriptPlugin(
    uint64_t                                                engineId,
    std::string                                             name,
    std::string                                             version,
    const std::optional<std::string>&                       description,
    std::optional<endstone::PluginLoadOrder>                load,
    const std::optional<std::vector<std::string>>&          authors,
    const std::optional<std::vector<std::string>>&          contributors,
    const std::optional<std::string>&                       website,
    const std::optional<std::string>&                       prefix,
    const std::optional<std::vector<std::string>>&          provides,
    const std::optional<std::vector<std::string>>&          depend,
    const std::optional<std::vector<std::string>>&          soft_depend,
    const std::optional<std::vector<std::string>>&          load_before,
    std::optional<endstone::PermissionDefault>              default_permission,
    const std::optional<std::vector<endstone::Command>>&    commands,
    const std::optional<std::vector<endstone::Permission>>& permissions
)
: engineId_(engineId),
  description_(
      std::move(name),
      std::move(version),
      description.value_or(""),
      load.value_or(endstone::PluginLoadOrder::PostWorld),
      authors.value_or(std::vector<std::string>{}),
      contributors.value_or(std::vector<std::string>{}),
      website.value_or(""),
      prefix.value_or(""),
      provides.value_or(std::vector<std::string>{}),
      depend.value_or(std::vector<std::string>{}),
      soft_depend.value_or(std::vector<std::string>{}),
      load_before.value_or(std::vector<std::string>{}),
      default_permission.value_or(endstone::PermissionDefault::Operator),
      commands.value_or(std::vector<endstone::Command>{}),
      permissions.value_or(std::vector<endstone::Permission>{})
  ) {}
// JavaScriptPlugin::~JavaScriptPlugin() {}

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