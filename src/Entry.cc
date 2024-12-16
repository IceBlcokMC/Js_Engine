#include "Entry.h"
#include "Engine/EngineManager.h"
#include "Loader/JavaScriptPlugin.h"
#include "Loader/JavaScriptPluginLoader.h"
#include "endstone/detail/logger_factory.h"
#include "endstone/detail/plugin/plugin_manager.h"
#include "endstone/detail/server.h"
#include "endstone/plugin/plugin_manager.h"
#include <debugapi.h>
#include <filesystem>
#include <memory>
#include <thread>
#include <utility>


ENDSTONE_PLUGIN("js_engine", "0.1.0", Entry) {
    description  = "JavaScript Engine";
    authors      = {"engsr6982"};
    contributors = {"engsr6982"};
    website      = "https://github.com/engsr6982/Js_Engine";
}


Entry* __Entry = nullptr;
Entry* GetEntry() { return __Entry; }


using endstone::detail::EndstoneServer;
void Entry::onLoad() {
    __Entry = this;
    getLogger().info("Js_Engine loading...");

#ifdef DEBUG
    getLogger().setLevel(endstone::Logger::Debug);
    getLogger().info("Waiting for VC debugger attach...");
    while (!IsDebuggerPresent()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
#endif
    // 不能在此注册加载器，否则会导致EndStone存放loader的vector重新分配内存，导致迭代器失效异常崩溃
}

void Entry::onEnable() {
    getLogger().info("Load javascript plugin...");
    auto& server        = getServer();
    auto& pluginManager = server.getPluginManager();
    pluginManager.registerLoader(std::make_unique<jse::JavaScriptPluginLoader>(server));
    pluginManager.loadPlugins(std::move(jse::JavaScriptPluginLoader::filterPlugins(fs::current_path() / "plugins")));


    getLogger().info("Js_Engine enabled");
}

void Entry::onDisable() {
    __Entry = nullptr;


    getLogger().info("Js_Engine disabled");
}
