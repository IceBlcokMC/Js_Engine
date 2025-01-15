#include "api/jse/JSEAPI.h"
#include "api/APIHelper.h"
#include "api/plugin/PluginAPI.h"
#include "manager/EngineData.h"
#include "utils/Using.h"
#include <iostream>


namespace jse {

ClassDefine<void> JSEAPI::builder = defineClass("JSE")
                                        .function("registerPlugin", &JSEAPI::registerPlugin)
                                        .function("getSelf", &JSEAPI::getSelf)
                                        .function("debug", &JSEAPI::debug)
                                        .build();

Local<Value> JSEAPI::registerPlugin(Arguments const& args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kObject);

    try {
        Local<Object> const& plugin  = args[0].asObject();
        ENGINE_DATA()->mRegisterInfo = script::Global<Object>(plugin);
        return Boolean::newBoolean(true);
    }
    Catch;
}

Local<Value> JSEAPI::getSelf(Arguments const&) {
    try {
        if (!ENGINE_DATA()->mPlugin) {
            return Local<Value>();
        }
        return PluginAPI::newPluginAPI(ENGINE_DATA()->mPlugin);
    }
    Catch;
}

Local<Value> JSEAPI::debug(Arguments const& args) {
    try {
        std::ostringstream oss;
        oss << "\033[1;42m";
        for (size_t i = 0; i < args.size(); ++i) ToString(args[i], oss);
        oss << "\033[0m";
        std::cout << oss.str() << std::endl;
        return Local<Value>();
    }
    Catch;
}

Local<Value> JSEAPI::isWindows(const Arguments& /* args */) {
#if defined(_WIN32) || defined(WIN32)
    return Boolean::newBoolean(true);
#endif
    return Boolean::newBoolean(false);
}

Local<Value> JSEAPI::isLinux(const Arguments& /* args */) {
#if defined(__linux__)
    return Boolean::newBoolean(true);
#endif
    return Boolean::newBoolean(false);
}

} // namespace jse