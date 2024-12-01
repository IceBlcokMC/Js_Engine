#include "Entry.h"
#include "Engine/Using.h"
#include "Engine/EngineManager.h"
#include "API/APIHelper.h"

ENDSTONE_PLUGIN("js_engine", "0.1.0", Entry)
{
    description = "JavaScript Engine";
}

// Entry *__Entry = new Entry();
Entry *__Entry = nullptr;
Entry *GetEntry()
{
    return __Entry;
}

void Entry::onLoad()
{
    __Entry = this;
    getLogger().info("Js_Engine loading...");
}

void Entry::onEnable()
{
    auto eng = jse::EngineManager::getInstance().createEngine();
    EngineScope scope(eng);
    jse::EngineManager::getEngineSelfData(eng).get()->mPluginName = "TestPlugin";

    try
    {
        eng->eval(R"(
            const a = {
                a: 1,
                b: 2,
                c: 3,
                d: [1, 2, 3, 4, 5],
                e: function() {
                    
                },
                f: {
                    g: 1,
                    h: 2,
                    i: 3
                }
            }
            logger.log(2,logger.log);
            logger.log(2,a);
            logger.log(3,'Hello World');
        )");
    }
    catch (script::Exception &e)
    {
        jse::PrintException(e);
    }

    getLogger().info("Js_Engine enabled");
}

void Entry::onDisable()
{
    __Entry = nullptr;
    getLogger().info("Js_Engine disabled");
}
