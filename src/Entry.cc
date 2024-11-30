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
#include <iostream>

script::Local<script::Value> SLOG(script::Arguments const &args)
{

    try
    {
        std::stringstream oss;
        for (int i = 0; i < args.size(); i++)
        {
            oss << args[i].asString().toString() << "";
        }
        std::cout << oss.str() << std::endl;

        return script::Boolean::newBoolean(true);
    }
    catch (script::Exception &e)
    {
        std::cout << e.what() << std::endl;
        return script::Boolean::newBoolean(false);
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
        return script::Boolean::newBoolean(false);
    }
    catch (...)
    {
        std::cout << "Unknown error" << std::endl;
        return script::Boolean::newBoolean(false);
    }
}

void Entry::onEnable()
{
    getLogger().info("Js_Engine enabled");
    // endstone::
    auto *eng = new script::ScriptEngineImpl();
    script::EngineScope scope(eng);

    eng->set("log", script::Function::newFunction(SLOG)); // bind function

    eng->eval("'use strict'");
    try
    {
        eng->eval(R"(
            'use strict'
            a = 1;
            b = 2;
            log("a + b = ", String(a + b));
        )");
    }
    catch (const script::Exception &e) {
        std::cerr << e.what() << '\n';
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    catch (...) {
        std::cerr << "Unknown error\n";
    }
}

void Entry::onDisable()
{
    getLogger().info("Js_Engine disabled");
}
