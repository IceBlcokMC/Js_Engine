#include "JavaScriptPluginLoader.h"
#include "Engine/EngineManager.h"
#include "Engine/Using.h"
#include "Entry.h"
#include "JavaScriptPlugin.h"
#include "endstone/detail/server.h"
#include "fmt/format.h"
#include <filesystem>
#include <iostream>

namespace jse {
namespace fs = std::filesystem;

JavaScriptPluginLoader::JavaScriptPluginLoader(endstone::Server& server) : PluginLoader(server) {}

std::vector<endstone::Plugin*> JavaScriptPluginLoader::loadPlugins(const std::string& directory) {
    std::vector<endstone::Plugin*> plugins;

    try {
        fs::path dir(directory);
        if (!fs::exists(dir)) {
            return plugins;
        }

        // 遍历目录查找.js文件
        for (const auto& entry : fs::directory_iterator(dir)) {
            if (entry.path().extension() == ".js") {
                if (auto plugin = loadPlugin(entry.path())) {
                    plugins.push_back(plugin);
                }
            }
        }
        
    } catch (const std::exception& e) {
        GetEntry()->getLogger().error(
            fmt::format("Error occurred while loading plugins from '{}': {}", directory, e.what())
        );
    }

    return plugins;
}

endstone::Plugin* JavaScriptPluginLoader::loadPlugin(const fs::path& file) {
    try {
        // 创建新的JS引擎实例
        auto& engineManager = EngineManager::getInstance();
        auto* engine        = engineManager.createEngine();
        if (!engine) {
            GetEntry()->getLogger().error(fmt::format("Failed to create JS engine for plugin: {}", file.string()));
            return nullptr;
        }
        EngineScope scope(engine); // 进入引擎作用域
        engine->loadFile(file.string());
        auto data = EngineManager::getEngineSelfData(engine);

        // 创建插件实例
        auto* plugin =
            new JavaScriptPlugin(data->mEngineId, data->mPluginName, data->mPluginVersion, data->mPluginDescription);

        // 执行JS文件


        return plugin;
    } catch (const std::exception& e) {
        GetEntry()->getLogger().error(fmt::format("Failed to load plugin '{}': {}", file.string(), e.what()));
        return nullptr;
    }
}

void JavaScriptPluginLoader::enablePlugin(endstone::Plugin& plugin) const {
    PluginLoader::enablePlugin(plugin);
    // TODO: 调用插件的enable回调
}

void JavaScriptPluginLoader::disablePlugin(endstone::Plugin& plugin) const {
    PluginLoader::disablePlugin(plugin);
    // TODO: 调用插件的disable回调
}

} // namespace jse
