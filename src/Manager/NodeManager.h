#pragma once
#include "Entry.h"
#include "Utils/Using.h"
#include "node.h"
#include "uv/uv.h"
#include "v8/v8.h"
#include <atomic>
#include <filesystem>
#include <memory>
#include <thread>
#include <unordered_map>
#include <vector>


namespace jse {


struct Package {
    string entry;                       // 入口文件
    bool   hasDependency{false};        // 是否有依赖
    bool   awaitInspectDebugger{false}; // 是否等待调试器
};

struct NodeWarpper {
    EngineID                                      mID;
    ScriptEngine*                                 mEngine;
    std::unique_ptr<node::CommonEnvironmentSetup> mEnvironment;
    bool                                          mIsRunning{false};
};

class NodeManager final {
private:
    NodeManager()                              = default;
    NodeManager(const NodeManager&)            = delete;
    NodeManager& operator=(const NodeManager&) = delete;

    bool                                        mIsInitialized{false}; // 是否初始化
    std::vector<string>                         mArgs;                 // 参数
    std::vector<string>                         mExecArgs;             // 执行参数
    std::unique_ptr<node::MultiIsolatePlatform> mPlatform;             // 平台
    std::unordered_map<EngineID, NodeWarpper>   mEngines;              // 引擎

public:
    static NodeManager& getInstance() {
        static NodeManager instance;
        return instance;
    }

    void initNodeJs() {
        if (mIsInitialized) {
            return;
        }

        auto workingDir = fs::current_path() / "bedrock_server.exe";
        mArgs           = {workingDir.string()};

        char* cWorkingDir = const_cast<char*>(workingDir.string().c_str());
        uv_setup_args(1, &cWorkingDir);

        std::vector<string> errors;
        if (node::InitializeNodeWithArgs(&mArgs, &mExecArgs, &errors) != 0) {
            Entry::getInstance()->getLogger().critical("Failed to initialize Node.js: ");
            for (auto const& error : errors) {
                Entry::getInstance()->getLogger().critical(error);
            }
            return;
        }

        mPlatform = node::MultiIsolatePlatform::Create(std::thread::hardware_concurrency());
        v8::V8::InitializePlatform(mPlatform.get());
        v8::V8::Initialize();
        mIsInitialized = true;
    }

    void shutdownNodeJs() {
        v8::V8::Dispose();
        v8::V8::ShutdownPlatform();
    }


public:
    bool hasEngine(EngineID id) const { return false; }

    ScriptEngine* newScriptEngine() {}

    ScriptEngine* getEngine(EngineID id) { return nullptr; }

    bool destroyEngine(EngineID id) { return false; }

    bool loadFile(EngineID id, fs::path const& path) { return false; }

    bool npm(string const& cmd = "npm install") {}
};


} // namespace jse
