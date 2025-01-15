#include "Loader/JavaScriptPluginLoader.h"
#include "Entry.h"
#include "Loader/JavaScriptPlugin.h"
#include "Manager/EngineData.h"
#include "Manager/NodeManager.h"
#include "Utils/Using.h"
#include "uv.h"
#include <cstddef>
#include <filesystem>
#include <memory>
#include <string>
#include <vector>

namespace jse {

JavaScriptPluginLoader::JavaScriptPluginLoader(endstone::Server& server) : PluginLoader(server) {}
std::vector<std::string> JavaScriptPluginLoader::getPluginFileFilters() const { return {".js"}; }

endstone::Plugin* JavaScriptPluginLoader::loadPlugin(std::string file) {
    auto& manager = NodeManager::getInstance();
    auto  wrapper = manager.newScriptEngine();

    EngineID id;
    {
        EngineScope enter(wrapper->mEngine);
        id = ENGINE_DATA()->mID;
    }

    try {
        auto path = fs::path(file);

        {
            EngineScope enter(wrapper->mEngine);
            ENGINE_DATA()->mFileName = path.filename().string();
        }

        fs::path package = path.parent_path() / "package.json";
        if (NodeManager::packageHasDependency(package) && !fs::exists(path.parent_path() / "node_modules")) {
            Entry::getInstance()->getLogger().info("Installing dependencies for plugin: {}", path.filename());
            EngineScope enter(wrapper->mEngine);
            manager.NpmInstall(path.parent_path().string());
        }

        bool const esm = NodeManager::packageIsEsm(package);
        if (!NodeManager::loadFile(wrapper, file, esm)) {
            Entry::getInstance()->getLogger().error("Failed to load plugin: {}", file);
            manager.destroyEngine(wrapper->mID);
            return nullptr;
        }

        {
            EngineScope enter(wrapper->mEngine);
            auto        data = ENGINE_DATA();

            if (esm) {
                size_t max   = 12; // 一般情况下, ESM 模块插件在第4个事件循环就会执行全局完全局代码
                size_t count = 0;
                while (count < max && data->mRegisterInfo.isEmpty()) {
                    count++;
                    uv_run(wrapper->mEnvSetup->event_loop(), UV_RUN_ONCE);
                }
                Entry::getInstance()->getLogger().debug("A total of {} event loops are executed", count);
                if (count == max && data->mRegisterInfo.isEmpty()) {
                    Entry::getInstance()->getLogger().warning("Failed to get plugin registration data, and the plugin "
                                                              "may not have called JSE.registerPlugin()");
                }
            }

            JsPluginDescriptionBuilder builder{};
            builder.description        = data->tryParseDescription();
            builder.load               = data->tryParseLoad();
            builder.authors            = data->tryParseAuthors();
            builder.contributors       = data->tryParseContributors();
            builder.website            = data->tryParseWebsite();
            builder.prefix             = data->tryParsePrefix();
            builder.provides           = data->tryParseProvides();
            builder.depend             = data->tryParseDepend();
            builder.soft_depend        = data->tryParseSoftDepend();
            builder.load_before        = data->tryParseLoadBefore();
            builder.default_permission = data->tryParseDefaultPermission();
            data->tryParseCommands(builder);
            data->tryParsePermissions(builder);

            // 创建插件实例
            auto plugin = new JavaScriptPlugin(data->mID, builder.build(data->tryParseName(), data->tryParseVersion()));
            data->mPlugin = plugin;

            return plugin;
        }
    } catch (script::Exception& e) {
        Entry::getInstance()->getLogger().error("Failed to load plugin: {}", file);
        // Entry::getInstance()->getLogger().error("JavaScript error: {}", e.what());
        // Entry::getInstance()->getLogger().error("Stack trace: {}", e.stacktrace());
    } catch (std::exception& e) {
        Entry::getInstance()->getLogger().error("Failed to load plugin: {}", file);
        Entry::getInstance()->getLogger().error("Unknown error: {}", e.what());
    } catch (...) {
        Entry::getInstance()->getLogger().error("Failed to load plugin: {}", file);
        Entry::getInstance()->getLogger().error("Unknown error");
    }

    manager.destroyEngine(id);
    return nullptr;
}


std::vector<std::string> JavaScriptPluginLoader::filterPlugins(const fs::path& directory) {
    std::vector<std::string> plugins;
    if (!fs::exists(directory)) {
        return plugins;
    }

    for (const auto& entry : fs::directory_iterator(directory)) {
        if (!entry.is_directory()) {
            continue;
        }

        fs::path package = entry.path() / "package.json";
        if (!fs::exists(package)) {
            continue;
        }

        auto main = NodeManager::findMainScript(package);
        if (!main) {
            continue;
        }

        plugins.push_back((entry.path() / *main).string());
    }

    return plugins;
}


} // namespace jse
