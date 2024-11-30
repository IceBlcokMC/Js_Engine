#include "LoggerAPI.h"
#include "Engine/EngineManager.h"
#include "Engine/EngineSelfData.h"
#include "APIHelper.h"
#include "Entry.h"

namespace jse
{
    ClassDefine<void> LoggerAPIBuilder =
        defineClass("logger")
            .function("log", &LoggerAPI::log)
            .function("info", &LoggerAPI::info)
            .function("warn", &LoggerAPI::warn)
            .function("error", &LoggerAPI::error)
            .function("debug", &LoggerAPI::debug)

            .function("colorLog", &LoggerAPI::colorLog)
            .function("format", &LoggerAPI::format)
            .build();

    Local<Value> LoggerAPI::log(Arguments const &args)
    {
        CheckArgsCount(args, 1);
        try
        {
            std::ostringstream oss;
            for (int i = 0; i < args.size(); ++i)
                ToString(args[i], oss);
            if (GetEntry())
            {
                auto data = EngineManager::getEngineSelfData(EngineScope::currentEngine());

                GetEntry()->getLogger().log(endstone::Logger::Level::Trace, fmt::format("[{}] {}", data.get()->mPluginName, oss.str()));

                return Boolean::newBoolean(true);
            }
            return Boolean::newBoolean(false);
        }
        Catch;
    }

    Local<Value> LoggerAPI::info(Arguments const &args)
    {
        return log(args);
    }

    Local<Value> LoggerAPI::warn(Arguments const &args)
    {
        return log(args);
    }

    Local<Value> LoggerAPI::error(Arguments const &args)
    {
        return log(args);
    }

    Local<Value> LoggerAPI::debug(Arguments const &args)
    {
        return log(args);
    }

    Local<Value> LoggerAPI::colorLog(Arguments const &args)
    {
        return log(args);
    }

    Local<Value> LoggerAPI::format(Arguments const &args)
    {
        return log(args);
    }

}