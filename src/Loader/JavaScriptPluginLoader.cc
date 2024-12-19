#include "JavaScriptPluginLoader.h"
#include "Engine/EngineData.h"
#include "Engine/EngineManager.h"
#include "Engine/Using.h"
#include "Entry.h"
#include "JavaScriptPlugin.h"
#include "Utils/Util.h"
#include "endstone/detail/server.h"
#include "endstone/permissions/permission_default.h"
#include "endstone/plugin/plugin_load_order.h"
#include "magic_enum/magic_enum.hpp"
#include "nlohmann/json.hpp"
#include "nlohmann/json_fwd.hpp"
#include <filesystem>
#include <memory>
#include <optional>
#include <string>
#include <vector>


namespace jse {

JavaScriptPluginLoader::JavaScriptPluginLoader(endstone::Server& server) : PluginLoader(server) {}
std::vector<std::string> JavaScriptPluginLoader::getPluginFileFilters() const { return {".js"}; }


endstone::Plugin* JavaScriptPluginLoader::loadPlugin(std::string file) {
    try {
        auto& manager = EngineManager::getInstance();
        auto  path    = fs::path(file);

        // 创建引擎
        auto        engine = manager.createEngine();
        EngineScope scope(engine);
        auto        data = ENGINE_DATA();

        // 加载文件
        data->mFileName = path.filename().string();
        engine->loadFile(file);

        // 解析注册数据
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
        auto plugin =
            new JavaScriptPlugin(data->mEngineId, builder.build(data->tryParseName(), data->tryParseVersion()));
        data->mPlugin = plugin;

        return plugin;
    } catch (script::Exception& e) {
        Entry::getInstance()->getLogger().error("Failed to load plugin: {}", file);
        Entry::getInstance()->getLogger().error("Error: {}", e.what());
    } catch (std::exception& e) {
        Entry::getInstance()->getLogger().error("Failed to load plugin: {}", file);
        Entry::getInstance()->getLogger().error("Error: {}", e.what());
    } catch (...) {
        Entry::getInstance()->getLogger().error("Failed to load plugin: {}", file);
        Entry::getInstance()->getLogger().error("Unknown error");
    }
    return nullptr;
}


std::vector<std::string> JavaScriptPluginLoader::filterPlugins(const fs::path& directory) {
    std::vector<std::string> plugins;
    if (!fs::exists(directory)) {
        return plugins;
    }

    for (const auto& entry : fs::directory_iterator(directory)) {
        if (entry.path().extension() == ".js") {
            plugins.push_back(entry.path().string());
        }
    }

    return plugins;
}


} // namespace jse
