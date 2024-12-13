#pragma once
#include "Engine/Using.h"
#include "Entry.h"
#include "Loader/JavaScriptPlugin.h"
#include "endstone/command/command.h"
#include "endstone/permissions/permission.h"
#include "endstone/permissions/permission_default.h"
#include "endstone/plugin/plugin_load_order.h"
#include "magic_enum/magic_enum.hpp"
#include <cstddef>
#include <cstdint>
#include <optional>
#include <utility>
#include <vector>


namespace jse {


struct EngineData {
    uint64_t               mEngineId{uint64_t(-1)};
    JavaScriptPlugin*      mPlugin{nullptr};
    string                 mFileName;
    script::Global<Object> mRegisterInfo;

public:
    void callOnLoad() {
        auto obj = mRegisterInfo.get();
        if (obj.has("onLoad")) {
            auto func = obj.get("onLoad");
            if (func.isFunction()) {
                func.asFunction().call();
                return;
            }
        }
        GetEntry()->getLogger().error("Plugin '{}' does not register onLoad function", this->mFileName);
    }

    void callOnEnable() {
        auto obj = mRegisterInfo.get();
        if (obj.has("onEnable")) {
            auto func = obj.get("onEnable");
            if (func.isFunction()) {
                func.asFunction().call();
                return;
            }
        }
        GetEntry()->getLogger().error("Plugin '{}' does not register onEnable function", this->mFileName);
    }

    void callOnDisable() {
        auto obj = mRegisterInfo.get();
        if (obj.has("onDisable")) {
            auto func = obj.get("onDisable");
            if (func.isFunction()) {
                func.asFunction().call();
                return;
            }
        }
        GetEntry()->getLogger().error("Plugin '{}' does not register onDisable function", this->mFileName);
    }

public:
    string parseName() {
        auto obj = mRegisterInfo.get();
        if (obj.has("name")) {
            return obj.get("name").asString().toString();
        }
        return this->mFileName;
    }
    string parseVersion() {
        auto obj = mRegisterInfo.get();
        if (obj.has("version")) {
            return obj.get("version").asString().toString();
        }
        return "0.0.0";
    }
    std::optional<string> parseDescription() {
        auto obj = mRegisterInfo.get();
        if (obj.has("description")) {
            return obj.get("description").asString().toString();
        }
        return std::nullopt;
    }
    std::optional<endstone::PluginLoadOrder> parseLoad() {
        auto obj = mRegisterInfo.get();
        if (obj.has("load")) {
            return magic_enum::enum_cast<endstone::PluginLoadOrder>(obj.get("load").asString().toString());
        }
        return std::nullopt;
    }
    std::optional<std::vector<string>> parseAuthors() {
        auto obj = mRegisterInfo.get();
        if (obj.has("authors")) {
            auto                array = obj.get("authors").asArray();
            std::vector<string> res;
            res.reserve(array.size());
            for (size_t i = 0; i < array.size(); i++) {
                res.push_back(array.get(i).asString().toString());
            }
            return std::move(res);
        }
        return std::nullopt;
    }
    std::optional<std::vector<string>> parseContributors() {
        auto obj = mRegisterInfo.get();
        if (obj.has("contributors")) {
            auto                array = obj.get("contributors").asArray();
            std::vector<string> res;
            res.reserve(array.size());
            for (size_t i = 0; i < array.size(); i++) {
                res.push_back(array.get(i).asString().toString());
            }
            return std::move(res);
        }
        return std::nullopt;
    }
    std::optional<string> parseWebsite() {
        auto obj = mRegisterInfo.get();
        if (obj.has("website")) {
            return obj.get("website").asString().toString();
        }
        return std::nullopt;
    }
    std::optional<string> parsePrefix() {
        auto obj = mRegisterInfo.get();
        if (obj.has("prefix")) {
            return obj.get("prefix").asString().toString();
        }
        return std::nullopt;
    }
    std::optional<std::vector<string>> parseProvides() {
        auto obj = mRegisterInfo.get();
        if (obj.has("provides")) {
            auto                array = obj.get("provides").asArray();
            std::vector<string> res;
            res.reserve(array.size());
            for (size_t i = 0; i < array.size(); i++) {
                res.push_back(array.get(i).asString().toString());
            }
            return std::move(res);
        }
        return std::nullopt;
    }
    std::optional<std::vector<string>> parseDepend() {
        auto obj = mRegisterInfo.get();
        if (obj.has("depend")) {
            auto                array = obj.get("depend").asArray();
            std::vector<string> res;
            res.reserve(array.size());
            for (size_t i = 0; i < array.size(); i++) {
                res.push_back(array.get(i).asString().toString());
            }
            return std::move(res);
        }
        return std::nullopt;
    }
    std::optional<std::vector<string>> parseSoftDepend() {
        auto obj = mRegisterInfo.get();
        if (obj.has("soft_depend")) {
            auto                array = obj.get("soft_depend").asArray();
            std::vector<string> res;
            res.reserve(array.size());
            for (size_t i = 0; i < array.size(); i++) {
                res.push_back(array.get(i).asString().toString());
            }
            return std::move(res);
        }
        return std::nullopt;
    }
    std::optional<std::vector<string>> parseLoadBefore() {
        auto obj = mRegisterInfo.get();
        if (obj.has("load_before")) {
            auto                array = obj.get("load_before").asArray();
            std::vector<string> res;
            res.reserve(array.size());
            for (size_t i = 0; i < array.size(); i++) {
                res.push_back(array.get(i).asString().toString());
            }
            return std::move(res);
        }
        return std::nullopt;
    }
    std::optional<endstone::PermissionDefault> parseDefaultPermission() {
        auto obj = mRegisterInfo.get();
        if (obj.has("default_permission")) {
            return magic_enum::enum_cast<endstone::PermissionDefault>(
                obj.get("default_permission").asString().toString()
            );
        }
        return std::nullopt;
    }
    std::optional<std::vector<endstone::Command>> parseCommands() {
        return std::nullopt; // TODO: implement
    }
    std::optional<std::vector<endstone::Permission>> parsePermissions() {
        return std::nullopt; // TODO: implement
    }
};


#define ENGINE_DATA() EngineScope::currentEngine()->getData<EngineData>()

#define GET_ENGINE_DATA(engine) engine->getData<EngineData>()


} // namespace jse