#include "API/JSE/EnumAPI.h"
#include "Utils/Using.h"
#include "Utils/Convert.h"
#include <endstone/game_mode.h>
#include <endstone/logger.h>
#include <endstone/permissions/permission_default.h>
#include <endstone/plugin/plugin_load_order.h>
#include <magic_enum/magic_enum.hpp>

#define REGISTER_ENUM_MACRO(ENUM, NAME)                                                                                \
    for (auto [value, key] : magic_enum::enum_entries<ENUM>()) {                                                       \
        enumMap[NAME][key] = static_cast<int>(value);                                                                  \
    }

namespace jse::EnumAPI {

void RegisterEnum(ScriptEngine* engine) {
    static std::unordered_map<std::string, std::unordered_map<std::string_view, int>> enumMap = []() {
        std::unordered_map<std::string, std::unordered_map<std::string_view, int>> map;
        REGISTER_ENUM_MACRO(endstone::PermissionDefault, "PermissionDefault");
        REGISTER_ENUM_MACRO(endstone::PluginLoadOrder, "PluginLoadOrder");
        REGISTER_ENUM_MACRO(endstone::Logger::Level, "LoggerLevel");
        REGISTER_ENUM_MACRO(endstone::GameMode, "GameMode");
        return map;
    }();

    engine->set("Enums", ConvertToScriptX(enumMap));
}

#undef REGISTER_ENUM_MACRO

} // namespace jse::EnumAPI