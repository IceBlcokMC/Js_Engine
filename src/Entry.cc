#include "Entry.h"
#include "Engine/EngineManager.h"
#include "Loader/JavaScriptPlugin.h"
#include "Loader/JavaScriptPluginLoader.h"
#include "endstone/detail/logger_factory.h"
#include "endstone/detail/plugin/plugin_manager.h"
#include "endstone/detail/server.h"
#include "endstone/plugin/plugin_manager.h"
#include <algorithm>
#include <debugapi.h>
#include <filesystem>
#include <memory>
#include <thread>
#include <utility>

using endstone::detail::EndstoneServer;

namespace jse {

Entry* Entry::getInstance() {
    static Entry* instance = new Entry();
    return instance;
}

void Entry::onLoad() {
#ifdef DEBUG
    getLogger().setLevel(endstone::Logger::Debug);
    getLogger().info("Waiting for VC debugger attach...");
    while (!IsDebuggerPresent()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
#endif
    getLogger().info("Load javascript plugin...");
    auto& server        = getServer();
    auto& pluginManager = server.getPluginManager();
    pluginManager.registerLoader(std::make_unique<jse::JavaScriptPluginLoader>(server));
    pluginManager.loadPlugins(std::move(jse::JavaScriptPluginLoader::filterPlugins(fs::current_path() / "plugins")));
}

void Entry::onEnable() {
    // getLogger().info("Load javascript plugin...");
    // auto& server        = getServer();
    // auto& pluginManager = server.getPluginManager();
    // pluginManager.registerLoader(std::make_unique<jse::JavaScriptPluginLoader>(server));
    // auto plugins =
    //     pluginManager.loadPlugins(std::move(jse::JavaScriptPluginLoader::filterPlugins(fs::current_path() /
    //     "plugins"))
    //     );
    // for (auto& plugin : plugins) {
    //     if (!plugin->isEnabled()) {
    //         pluginManager.enablePlugin(*plugin); // 由于 onEnable 流程结束，这里手动调用 enablePlugin
    //     }
    // }
}

void Entry::onDisable() {}

endstone::PluginDescription const& Entry::getDescription() const { return description_; }

} // namespace jse

extern "C" __declspec(dllexport) endstone::Plugin* init_endstone_plugin() { return jse::Entry::getInstance(); }