#include "EndStoneAPI.h"

#include "APIHelper.h"
#include "Engine/EngineManager.h"
#include "Entry.h"
#include "fmt/core.h"


namespace jse {
ClassDefine<void> EndStoneAPIClass =
    defineClass("endstone").function("registerPlugin", &EndStoneAPI::registerPlugin).build();

Local<Value> EndStoneAPI::registerPlugin(Arguments const& args) {
    /*
        endstone.registerPlugin({
            name: string,
            version: `x.x.x`,
            description: string,
        });
     */
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kObject);

    try {
        auto          data   = EngineManager::getEngineSelfData(EngineScope::currentEngine()).get();
        Local<Object> plugin = args[0].asObject();
        if (plugin.has("name")) {
            data->mPluginName = plugin.get("name").asString().toString();
        } else {
            data->mFileName = data->mFileName;
            GetEntry()->getLogger().warning(fmt::format(
                "Plugin name is not specified, use file name as plugin name, file name: {}",
                data->mFileName
            ));
        }

        if (plugin.has("version")) {
            data->mPluginVersion = plugin.get("version").asString().toString();
        }
        if (plugin.has("description")) {
            data->mPluginDescription = plugin.get("description").asString().toString();
        }
        return Boolean::newBoolean(true);
    }
    Catch;
}

} // namespace jse