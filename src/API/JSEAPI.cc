#include "JSEAPI.h"
#include "APIHelper.h"
#include "Engine/EngineData.h"
#include "Engine/EngineManager.h"
#include "Entry.h"
#include "PluginAPI.h"
#include "Utils/Using.h"
#include "fmt/core.h"
#include <iostream>


namespace jse {

ClassDefine<void> JSEAPI::builder = defineClass("JSE")
                                        .function("registerPlugin", &JSEAPI::registerPlugin)
                                        .function("getPlugin", &JSEAPI::getPlugin)
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

Local<Value> JSEAPI::getPlugin(Arguments const&) {
    try {
        return PluginAPI::newPluginAPI();
    }
    Catch;
}

Local<Value> JSEAPI::debug(Arguments const& args) {
    try {
        std::ostringstream oss;
        oss << "\033[1;42m";
        for (int i = 0; i < args.size(); ++i) ToString(args[i], oss);
        oss << "\033[0m";
        std::cout << oss.str() << std::endl;
        return Local<Value>();
    }
    Catch;
}


} // namespace jse