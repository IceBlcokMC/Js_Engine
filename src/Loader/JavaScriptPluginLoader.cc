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
    auto& manager = EngineManager::getInstance();
    auto  path    = fs::path(file);

    // 创建引擎
    auto        engine = manager.createEngine();
    EngineScope scope(engine);
    auto        data = ENGINE_DATA();

    data->mFileName = path.filename().string();
    engine->loadFile(file);

    // 解析注册数据创建 Plugin 实例
    auto plugin = new JavaScriptPlugin(
        data->mEngineId,
        data->parseName(),
        data->parseVersion(),
        data->parseDescription(),
        data->parseLoad(),
        data->parseAuthors(),
        data->parseContributors(),
        data->parseWebsite(),
        data->parsePrefix(),
        data->parseProvides(),
        data->parseDepend(),
        data->parseSoftDepend(),
        data->parseLoadBefore(),
        data->parseDefaultPermission(),
        data->parseCommands(),
        data->parsePermissions()
    );
    data->mPlugin = plugin;

    return plugin;
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
