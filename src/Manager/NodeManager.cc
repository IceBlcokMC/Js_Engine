#include "NodeManager.h"
#include "API/APIHelper.h"
#include "BindAPI.h"
#include "EngineData.h"
#include "Entry.h"
#include "Utils/Util.h"
#include "env.h"
#include "fmt/core.h"
#include "nlohmann/json.hpp"
#include "uv/uv.h"
#include "v8/v8.h"
#include <filesystem>
#include <thread>
#include <unordered_map>
#include <utility>


namespace jse {


NodeManager& NodeManager::getInstance() {
    static NodeManager instance;
    return instance;
}

void NodeManager::initNodeJs() {
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

void NodeManager::shutdownNodeJs() {
    v8::V8::Dispose();
    v8::V8::ShutdownPlatform();
}


bool NodeManager::hasEngine(EngineID id) const { return mEngines.contains(id); }

EngineID NodeManager::getEngineID(node::Environment* env) const {
    if (mEnvMap.contains(env)) {
        return mEnvMap.at(env);
    }
    return -1;
}

ScriptEngine* NodeManager::newScriptEngine() {
    static EngineID NextEngineID = 0;
    if (!mIsInitialized) {
        return nullptr;
    }
    EngineID id = NextEngineID++;

    std::vector<string>                           errors;
    std::unique_ptr<node::CommonEnvironmentSetup> envSetup =
        node::CommonEnvironmentSetup::Create(mPlatform.get(), &errors, mArgs, mExecArgs);
    if (!envSetup) {
        for (auto const& err : errors)
            Entry::getInstance()->getLogger().error("Faild to create environment setup: {}", err);
        return nullptr;
    }

    v8::Isolate*       isolate = envSetup->isolate();
    node::Environment* env     = envSetup->env();

    v8::Locker         locker(isolate);
    v8::Isolate::Scope isolateScope(isolate);
    v8::HandleScope    handleScope(isolate);
    v8::Context::Scope contextScope(envSetup->context());

    ScriptEngine* engine = new ScriptEngineImpl({}, isolate, envSetup->context(), false);

    NodeWrapper warpper{NextEngineID, {}, engine, std::move(envSetup), true};
    mEnvMap.insert({env, id});
    mEngines.insert({NextEngineID, std::move(warpper)});

    node::AddEnvironmentCleanupHook(
        isolate,
        [](void* arg) {
            static_cast<ScriptEngine*>(arg)->destroy();
            Entry::getInstance()->getLogger().debug("Destroyed engine: {}", arg);
        },
        engine
    );

    return engine;
}

ScriptEngine* NodeManager::getEngine(EngineID id) {
    if (mEngines.contains(id)) {
        return mEngines[id].mEngine;
    }
    return nullptr;
}

bool NodeManager::destroyEngine(EngineID id) {
    if (!hasEngine(id)) {
        return false;
    }

    auto& warpper      = mEngines[id];
    warpper.mIsRunning = false;

    node::Stop(warpper.mEnvSetup->env());

    // TODO: Stop uv_loop

    return true;
}

bool NodeManager::loadFile(EngineID id, fs::path const& path) {
    if (!hasEngine(id)) {
        return false;
    }

    auto& wrapper = mEngines[id];
    auto* env     = wrapper.mEnvSetup->env();
    auto* isolate = wrapper.mEnvSetup->isolate();

    auto js_code = this->readFileContent(path);
    if (!js_code) {
        return false;
    }

    string dirname  = ReplaceWinPath(path.parent_path().string());
    string filename = ReplaceWinPath(path.filename().string());

    try {
        EngineScope enter(wrapper.mEngine);

        if (wrapper.mPackage.awaitInspectDebugger) {
            static string debug_wait_code = R"(
                process._debugProcess(process.pid);
                const startTime = Date.now();
                const timeout = 30000; // 30秒超时
                while (!process.debugPort) {
                    if (Date.now() - startTime > timeout) {
                        console.error('等待调试器超时');
                        break;
                    }
                }
            )";

            node::LoadEnvironment(env, debug_wait_code.c_str());
        }

        // TODO: ECMAScript Module Support
        // Node.Js 22 的 ESM 和 16 写法不同、需查找16的写法
        static string prepare_code = R"(
                const PublicRequire = require('module').createRequire(`${process.cwd()}/ {0} `);
                const PublicModule = require('module');
                PublicModule.exports = {};
                (function(exports, require, module, __filename, __dirname){ {1} })
                ({}, PublicRequire, PublicModule, '{2}', '{3}');
            )";
        string        compiler = RuntimeFormat(prepare_code, dirname, js_code.value(), filename, dirname).value_or("");
        if (compiler.empty()) {
            Entry::getInstance()->getLogger().error("Failed to compile code");
            return false;
        }

        node::SetProcessExitHandler(env, [this](node::Environment* env_, int exit_code) {
            Entry::getInstance()->getLogger().debug("Node.js process exit with code: {}", exit_code);
            auto id = this->getEngineID(env_);
            if (id != -1) {
                this->destroyEngine(id);
            }
        });

        v8::MaybeLocal<v8::Value> loadValue = node::LoadEnvironment(env, compiler.c_str());
        if (loadValue.IsEmpty()) {
            node::Stop(env);
            uv_stop(wrapper.mEnvSetup->event_loop());
            return false;
        }

        // TODO: uv_run
        //  EngineScope enter(engine);
        //  uv_run(eventLoop, UV_RUN_NOWAIT);

        return true;
    } catch (...) {
        return false;
    }
}

bool NodeManager::npm(string const& cmd, string npmExecuteDir) {
    if (!mIsInitialized) {
        return false;
    }

    std::vector<std::string> errors;
    auto                     setup = node::CommonEnvironmentSetup::Create(
        mPlatform.get(),
        &errors,
        mArgs,
        mExecArgs,
        node::EnvironmentFlags::kOwnsProcessState
    );
    if (!setup) {
        for (const std::string& err : errors)
            Entry::getInstance()->getLogger().error("CommonEnvironmentSetup Error: {}", err.c_str());
        return false;
    }
    npmExecuteDir = ReplaceWinPath(npmExecuteDir);

    v8::Isolate*       isolate = setup->isolate();
    node::Environment* env     = setup->env();

    v8::Locker         locker(isolate);
    v8::Isolate::Scope isolate_scope(isolate);
    v8::HandleScope    handle_scope(isolate);
    v8::Context::Scope context_scope(setup->context());

    static string prepare_code = R"(
            const cwd = process.cwd();
            const PublicRequire = require('module').createRequire(`${cwd}/plugins/js_engine`);
            require("process").chdir(`{0}`);
            PublicRequire("npm-js-interface")(`{1}`);
            require("process").chdir(cwd);
        )";

    string compiler = RuntimeFormat(prepare_code, npmExecuteDir, cmd).value_or("");
    if (compiler.empty()) {
        Entry::getInstance()->getLogger().error("Failed to compile code, npm command: {}", cmd);
        node::Stop(env);
        return false;
    }

    bool success = false;
    try {
        node::SetProcessExitHandler(env, [&](node::Environment* env_, int exit_code) { node::Stop(env); });
        v8::MaybeLocal<v8::Value> loadValue = node::LoadEnvironment(env, compiler.c_str());
        if (loadValue.IsEmpty()) {
            throw std::runtime_error("Failed to load environment");
        }
        success = node::SpinEventLoop(env).FromMaybe(1) == 0;
    } catch (...) {
        Entry::getInstance()->getLogger().error("Failed to run npm command: {}", cmd);
    }

    node::Stop(env);
    return success;
}


std::optional<string> NodeManager::readFileContent(const fs::path& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        Entry::getInstance()->getLogger().error("Cannot open file: {}", path.string());
        return std::nullopt;
    }
    string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();
    return std::move(content);
}

std::optional<Package> NodeManager::parsePackage(const fs::path& packagePath) {
    try {
        if (!fs::exists(packagePath)) {
            Entry::getInstance()->getLogger().error("Package.json not found: {}", packagePath.string());
            return std::nullopt;
        }

        auto content = readFileContent(packagePath);
        if (!content) {
            return std::nullopt;
        }

        auto json = nlohmann::json::parse(*content);
        return Package{
            .entry                = json.value("main", ""),
            .hasDependency        = json.contains("dependencies"),
            .awaitInspectDebugger = json.value("awaitInspectDebugger", false),
        };
    } catch (...) {
        return std::nullopt;
    }
}


} // namespace jse
