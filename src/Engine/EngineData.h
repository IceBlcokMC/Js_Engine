#pragma once
#include "Engine/Using.h"
#include "Entry.h"
#include "Loader/JavaScriptPlugin.h"
#include "Utils/Convert.h"
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
    string                 mFileName;
    script::Global<Object> mRegisterInfo;

    JavaScriptPlugin* mPlugin{nullptr};

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
        Entry::getInstance()->getLogger().error("Plugin '{}' does not register onLoad function", this->mFileName);
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
        Entry::getInstance()->getLogger().error("Plugin '{}' does not register onEnable function", this->mFileName);
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
        Entry::getInstance()->getLogger().error("Plugin '{}' does not register onDisable function", this->mFileName);
    }

public:
    string tryParseName() {
        auto obj = mRegisterInfo.get();
        if (obj.has("name")) {
            return obj.get("name").asString().toString();
        }
        return this->mFileName;
    }
    string tryParseVersion() {
        auto obj = mRegisterInfo.get();
        if (obj.has("version")) {
            return obj.get("version").asString().toString();
        }
        return "0.0.0";
    }
    string tryParseDescription() {
        auto obj = mRegisterInfo.get();
        if (obj.has("description")) {
            return obj.get("description").asString().toString();
        }
        return "";
    }
    endstone::PluginLoadOrder tryParseLoad() {
        auto obj = mRegisterInfo.get();
        if (obj.has("load")) {
            return *magic_enum::enum_cast<endstone::PluginLoadOrder>(obj.get("load").asString().toString());
        }
        return endstone::PluginLoadOrder::PostWorld;
    }
    std::vector<string> tryParseAuthors() {
        auto obj = mRegisterInfo.get();
        if (obj.has("authors")) {
            return ConvertFromScriptX<std::vector<string>>(obj.get("authors").asArray());
        }
        return {};
    }
    std::vector<string> tryParseContributors() {
        auto obj = mRegisterInfo.get();
        if (obj.has("contributors")) {
            return ConvertFromScriptX<std::vector<string>>(obj.get("contributors").asArray());
        }
        return {};
    }
    string tryParseWebsite() {
        auto obj = mRegisterInfo.get();
        if (obj.has("website")) {
            return obj.get("website").asString().toString();
        }
        return "";
    }
    string tryParsePrefix() {
        auto obj = mRegisterInfo.get();
        if (obj.has("prefix")) {
            return obj.get("prefix").asString().toString();
        }
        return "";
    }
    std::vector<string> tryParseProvides() {
        auto obj = mRegisterInfo.get();
        if (obj.has("provides")) {
            return ConvertFromScriptX<std::vector<string>>(obj.get("provides").asArray());
        }
        return {};
    }
    std::vector<string> tryParseDepend() {
        auto obj = mRegisterInfo.get();
        if (obj.has("depend")) {
            return ConvertFromScriptX<std::vector<string>>(obj.get("depend").asArray());
        }
        return {};
    }
    std::vector<string> tryParseSoftDepend() {
        auto obj = mRegisterInfo.get();
        if (obj.has("soft_depend")) {
            return ConvertFromScriptX<std::vector<string>>(obj.get("soft_depend").asArray());
        }
        return {};
    }
    std::vector<string> tryParseLoadBefore() {
        auto obj = mRegisterInfo.get();
        if (obj.has("load_before")) {
            return ConvertFromScriptX<std::vector<string>>(obj.get("load_before").asArray());
        }
        return {};
    }
    endstone::PermissionDefault tryParseDefaultPermission() {
        auto obj = mRegisterInfo.get();
        if (obj.has("default_permission")) {
            return ConvertFromScriptX<endstone::PermissionDefault>(obj.get("default_permission").asString());
        }
        return endstone::PermissionDefault::Operator;
    }

public:
    void tryParseCommands(JsPluginDescriptionBuilder& jbuilder) {
        auto obj = mRegisterInfo.get();
        if (!obj.has("commands")) {
            return;
        }

        auto cmds = obj.get("commands").asObject();
        auto keys = cmds.getKeyNames();
        for (auto& key : keys) {
            auto cmdObj  = cmds.get(key).asObject();
            auto builder = endstone::detail::CommandBuilder(key);

            // 描述
            if (cmdObj.has("description")) {
                builder.description(ConvertFromScriptX<string>(cmdObj.get("description")));
            }

            // 用法
            if (cmdObj.has("usages")) {
                auto usages = ConvertFromScriptX<std::vector<string>>(cmdObj.get("usages"));
                for (const auto& usage : usages) {
                    builder.usages(usage);
                }
            }

            // 权限
            if (cmdObj.has("permissions")) {
                auto permissions = ConvertFromScriptX<std::vector<string>>(cmdObj.get("permissions"));
                for (const auto& permission : permissions) {
                    builder.permissions(permission);
                }
            }

            jbuilder.commands.emplace(key, std::move(builder));
        }
    }


    void tryParsePermissions(JsPluginDescriptionBuilder& jbuilder) {
        auto obj = mRegisterInfo.get();
        if (!obj.has("permissions")) {
            return;
        }

        auto perms = obj.get("permissions").asObject();
        auto keys  = perms.getKeyNames();
        for (auto& key : keys) {
            auto permObj = perms.get(key).asObject();
            auto builder = endstone::detail::PermissionBuilder(key);

            // 设置描述
            if (permObj.has("description")) {
                builder.description(ConvertFromScriptX<string>(permObj.get("description")));
            }

            // 设置默认权限
            if (permObj.has("default")) {
                builder.default_(ConvertFromScriptX<endstone::PermissionDefault>(permObj.get("default")));
            }

            jbuilder.permissions.emplace(key, std::move(builder));
        }
    }
};


#define ENGINE_DATA() EngineScope::currentEngine()->getData<EngineData>()

#define GET_ENGINE_DATA(engine) engine->getData<EngineData>()


} // namespace jse