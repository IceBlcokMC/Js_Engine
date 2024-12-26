#pragma once
#include "Utils/Using.h"
#include "node.h"
#include <filesystem>
#include <memory>
#include <optional>
#include <unordered_map>
#include <vector>


namespace jse {


struct Package {
    string entry;                       // 入口文件
    bool   hasDependency{false};        // 是否有依赖
    bool   awaitInspectDebugger{false}; // 是否等待调试器
};

struct NodeWrapper {
    EngineID                                      mID;
    Package                                       mPackage;
    ScriptEngine*                                 mEngine;
    std::unique_ptr<node::CommonEnvironmentSetup> mEnvSetup;
    bool                                          mIsRunning{false};
};

class NodeManager final {
private:
    NodeManager()                              = default;
    NodeManager(const NodeManager&)            = delete;
    NodeManager& operator=(const NodeManager&) = delete;

    bool                                             mIsInitialized{false}; // 是否初始化
    std::vector<string>                              mArgs;                 // 参数
    std::vector<string>                              mExecArgs;             // 执行参数
    std::unique_ptr<node::MultiIsolatePlatform>      mPlatform;             // v8 平台
    std::unordered_map<EngineID, NodeWrapper>        mEngines;              // 引擎列表
    std::unordered_map<node::Environment*, EngineID> mEnvMap;               // 环境映射

public:
    static NodeManager& getInstance();

    void initNodeJs();

    void shutdownNodeJs();

public:
    bool hasEngine(EngineID id) const;

    EngineID getEngineID(node::Environment* env) const;

    ScriptEngine* newScriptEngine();

    ScriptEngine* getEngine(EngineID id);

    bool destroyEngine(EngineID id);

    bool loadFile(EngineID id, fs::path const& file);

    bool npm(string const& cmd = "npm install", string npmExecuteDir = "plugins/js_engine");

public:
    std::optional<string> readFileContent(const fs::path& file);

    std::optional<Package> parsePackage(const fs::path& packagePath);
};


} // namespace jse
