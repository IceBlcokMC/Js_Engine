#pragma once
#include "utils/Using.h"
#include <atomic>
#include <endstone/scheduler/task.h>
#include <filesystem>
#include <memory>
#include <node.h>
#include <optional>
#include <unordered_map>
#include <vector>

namespace jse {


struct EngineWrapper {
    EngineID                                      mID; // 引擎ID
    ScriptEngine*                                 mEngine;
    std::unique_ptr<node::CommonEnvironmentSetup> mEnvSetup;
    // std::shared_ptr<endstone::Task>               mUvLoopTask{nullptr};
    bool mIsRunning{false};
    bool mIsDestroying{false};

public:
    EngineWrapper() = default;
    EngineWrapper(EngineID id, ScriptEngine* engine, std::unique_ptr<node::CommonEnvironmentSetup> envs)
    : mID(id),
      mEngine(engine),
      mEnvSetup(std::move(envs)) {}

    operator ScriptEngine*() const { return mEngine; }
};

using EngineWrapperPtr = std::unique_ptr<EngineWrapper>;

class NodeManager final {
private:
    NodeManager()                              = default;
    NodeManager(const NodeManager&)            = delete;
    NodeManager& operator=(const NodeManager&) = delete;

    bool                                           mIsInitialized{false}; // 是否初始化
    std::vector<string>                            mArgs;                 // 参数
    std::vector<string>                            mExecArgs;             // 执行参数
    std::unique_ptr<node::MultiIsolatePlatform>    mPlatform;             // v8 平台
    std::unordered_map<EngineID, EngineWrapperPtr> mEngines;              // 引擎列表

    std::atomic<bool> mUvLoopThreadRunning{true}; // uv loop 线程是否在运行

public:
    static NodeManager& getInstance();

    void initNodeJs();

    void shutdownNodeJs();

    void initUvLoopThread();
    void shutdownUvLoopThread();

public:
    bool hasEngine(EngineID id) const;

    EngineWrapper* newScriptEngine();

    EngineWrapper* getEngine(EngineID id);

    bool destroyEngine(EngineID id);

    bool NpmInstall(string npmExecuteDir);

public:
    static bool loadFile(EngineWrapper* wrapper, fs::path const& file, bool esm = false);

    static std::optional<string> readFileContent(const fs::path& file);

    static std::optional<string> findMainScript(const fs::path& packagePath);
    static bool                  packageHasDependency(const fs::path& packagePath);
    static bool                  packageIsEsm(const fs::path& packagePath);
};


} // namespace jse
