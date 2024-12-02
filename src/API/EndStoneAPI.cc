#include "EndStoneAPI.h"

#include "APIHelper.h"
#include "Engine/EngineManager.h"
#include "Entry.h"
#include "fmt/core.h"


namespace jse {
ClassDefine<void> EndStoneAPIClass =
    defineClass("JSE_EndStone").function("register_plugin", &EndStoneAPI::register_plugin).build();

Local<Value> EndStoneAPI::register_plugin(Arguments const& args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kObject);

    try {
        Local<Object> const& plugin = args[0].asObject();
        auto                 data   = EngineManager::getEngineSelfData(EngineScope::currentEngine()).get();
        data->mJSE_Plugin           = script::Global<Object>(plugin); // 保存到引擎强引用中（防止Gc）
        return Boolean::newBoolean(true);
    }
    Catch;
}

} // namespace jse