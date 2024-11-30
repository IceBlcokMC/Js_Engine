#include "Entry.h"

ENDSTONE_PLUGIN("js_engine", "0.1.0", Entry)
{
    description = "JavaScript Engine";
}

void Entry::onLoad()
{
    getLogger().info("Js_Engine loading...");
}

#include <endstone/command/command.h>
#include <ScriptX/ScriptX.h>

void Entry::onEnable()
{
    getLogger().info("Js_Engine enabled");
    // endstone::
    auto *eng = new script::ScriptEngineImpl();
    auto v = eng->eval("4444444");
    getLogger().warning("Js_Engine result: ", v.asNumber().toInt32());
}

void Entry::onDisable()
{
    getLogger().info("Js_Engine disabled");
}
