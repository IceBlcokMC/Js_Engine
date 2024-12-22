#include "Entry.h"
#include "Engine/EngineManager.h"
#include "Loader/JavaScriptPluginLoader.h"
#include "Utils/Using.h"
#include "endstone/plugin/plugin_manager.h"

#include <filesystem>
#include <memory>
#include <thread>
#include <utility>

#if (defined(WIN32) || defined(_WIN32)) && defined(DEBUG)
#include <debugapi.h>
#endif

namespace jse {

Entry* Entry::getInstance() {
    static Entry* instance = new Entry();
    return instance;
}

void Entry::onLoad() {
#if (defined(WIN32) || defined(_WIN32)) && defined(DEBUG)
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
    EngineManager::getInstance().initMessageLoop();
}

void Entry::onEnable() {}
void Entry::onDisable() { EngineManager::getInstance().stopMessageLoop(); }

endstone::PluginDescription const& Entry::getDescription() const { return description_; }

} // namespace jse


#if defined(WIN32) || defined(_WIN32)
#define EXPORT_ENTRY_POINT __declspec(dllexport)
#else
#define EXPORT_ENTRY_POINT __attribute__((visibility("default")))
#endif
extern "C" [[maybe_unused]] EXPORT_ENTRY_POINT endstone::Plugin* init_endstone_plugin() {
    return jse::Entry::getInstance();
}
