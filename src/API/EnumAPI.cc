#include "EnumAPI.h"
#include "APIHelper.h"
#include "Utils/Using.h"
#include <endstone/permissions/permission_default.h>
#include <string>
#include <unordered_map>

#define REGISTER_ENUM_MACRO(ENUM, NAME)                                                                                \
    for (auto [value, key] : magic_enum::enum_entries<ENUM>()) {                                                       \
        enumMap[NAME][key] = static_cast<int>(value);                                                                  \
    }

namespace jse::EnumAPI {

void RegisterEnum(ScriptEngine* engine) {
    static Local<Value> enumMap = ([]() -> Local<Value> {
        std::unordered_map<std::string, std::unordered_map<std::string_view, int>> enumMap;

        REGISTER_ENUM_MACRO(endstone::PermissionDefault, "PermissionDefault");
        REGISTER_ENUM_MACRO(endstone::PluginLoadOrder, "PluginLoadOrder");
        REGISTER_ENUM_MACRO(endstone::Logger::Level, "LoggerLevel");

        return ConvertToScriptX(enumMap);
    })();

    engine->set("Enums", enumMap);
}

#undef REGISTER_ENUM_MACRO

} // namespace jse::EnumAPI