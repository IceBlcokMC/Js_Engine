#include "EndStoneAPI.h"
#include "APIHelper.h"
#include "Engine/EngineData.h"
#include "Engine/EngineManager.h"
#include "Engine/Using.h"
#include "Entry.h"
#include "PluginAPI.h"
#include "fmt/core.h"


namespace jse {

ClassDefine<void> EndStoneAPIClass = defineClass("JSE_EndStone")
                                         .function("register_plugin", &EndStoneAPI::register_plugin)
                                         .function("get_plugin", &EndStoneAPI::get_plugin)
                                         .build();


Local<Value> EndStoneAPI::register_plugin(Arguments const& args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kObject);

    try {
        Local<Object> const& plugin  = args[0].asObject();
        ENGINE_DATA()->mRegisterInfo = script::Global<Object>(plugin);
        return Boolean::newBoolean(true);
    }
    Catch;
}

Local<Value> EndStoneAPI::get_plugin(Arguments const&) {
    try {
        return PluginAPI::newPluginAPI();
    }
    Catch;
}

} // namespace jse