#include "JavaScriptPluginLoader.h"
#include "Entry.h"
#include "JavaScriptPlugin.h"
#include "Manager/EngineData.h"
#include "Manager/NodeManager.h"
#include "Utils/Using.h"
#include <filesystem>
#include <memory>
#include <string>
#include <vector>


namespace jse {

JavaScriptPluginLoader::JavaScriptPluginLoader(endstone::Server& server) : PluginLoader(server) {}
std::vector<std::string> JavaScriptPluginLoader::getPluginFileFilters() const { return {".js"}; }

#define LOAD_CATCH(TYPE, ...)                                                                                          \
    catch (TYPE & e) {                                                                                                 \
        Entry::getInstance()->getLogger().error("Failed to load plugin: {}", file);                                    \
        Entry::getInstance()->getLogger().error("Error: {}", e.what());                                                \
        __VA_ARGS__;                                                                                                   \
    }

endstone::Plugin* JavaScriptPluginLoader::loadPlugin(std::string file) {
    // auto&       manager = EngineManager::getInstance();
    // auto        engine  = manager.createEngine();
    // EngineScope scope(engine);
    // auto        data = ENGINE_DATA();
    // try {
    //     auto path = fs::path(file);

    //     // 加载文件
    //     data->mFileName = path.filename().string();
    //     engine->loadFile(file);

    //     // 解析注册数据
    //     JsPluginDescriptionBuilder builder{};
    //     builder.description        = data->tryParseDescription();
    //     builder.load               = data->tryParseLoad();
    //     builder.authors            = data->tryParseAuthors();
    //     builder.contributors       = data->tryParseContributors();
    //     builder.website            = data->tryParseWebsite();
    //     builder.prefix             = data->tryParsePrefix();
    //     builder.provides           = data->tryParseProvides();
    //     builder.depend             = data->tryParseDepend();
    //     builder.soft_depend        = data->tryParseSoftDepend();
    //     builder.load_before        = data->tryParseLoadBefore();
    //     builder.default_permission = data->tryParseDefaultPermission();
    //     data->tryParseCommands(builder);
    //     data->tryParsePermissions(builder);

    //     // 创建插件实例
    //     auto plugin =
    //         new JavaScriptPlugin(data->mEngineId, builder.build(data->tryParseName(), data->tryParseVersion()));
    //     data->mPlugin = plugin;

    //     return plugin;
    // }
    // LOAD_CATCH(script::Exception, Entry::getInstance()->getLogger().error("Stacktrace: \n{}", e.stacktrace()))
    // LOAD_CATCH(std::exception) catch (...) {
    //     Entry::getInstance()->getLogger().error("Failed to load plugin: {}", file);
    //     Entry::getInstance()->getLogger().error("Unknown error");
    // }
    // manager.destroyEngine(data->mEngineId);
    return nullptr;
}

#undef LOAD_CATCH

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
