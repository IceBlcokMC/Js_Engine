#include "LoggerAPI.h"
#include "APIHelper.h"
#include "Engine/EngineData.h"
#include "Engine/EngineManager.h"
#include "Entry.h"
#include "fmt/args.h"
#include "fmt/format.h"


namespace jse {

ClassDefine<void> LoggerAPIClass = defineClass("JSE_Logger")
                                       .function("log", &LoggerAPI::log)
                                       .function("info", &LoggerAPI::info)
                                       .function("warning", &LoggerAPI::warning)
                                       .function("error", &LoggerAPI::error)
                                       .function("debug", &LoggerAPI::debug)
                                       .function("trace", &LoggerAPI::trace)
                                       .function("critical", &LoggerAPI::critical)
                                       .function("setLevel", &LoggerAPI::setLevel)
                                       .function("isEnabledFor", &LoggerAPI::isEnabledFor)
                                       .function("getName", &LoggerAPI::getName)
                                       .build();

Local<Value> LoggerAPIHelper(endstone::Logger::Level level, string const& message) {
    try {
        auto data = ENGINE_DATA();
        if (data->mPlugin) {
            data->mPlugin->getLogger().log(level, message);
            return Boolean::newBoolean(true);
        }
        return Boolean::newBoolean(false);
    }
    Catch;
}
Local<Value> LoggerAPIHelper(endstone::Logger::Level level, Arguments const& args, int start = 0) {
    try {
        std::ostringstream oss;
        for (int i = start; i < args.size(); ++i) ToString(args[i], oss);
        return LoggerAPIHelper(level, oss.str());
    }
    Catch;
}

Local<Value> LoggerAPI::log(Arguments const& args) {
    // CheckArgsCount(args, 2);
    // CheckArgType(args[0], ValueKind::kNumber);
    // CheckArgType(args[1], ValueKind::kString); // any
    return LoggerAPIHelper(static_cast<endstone::Logger::Level>(args[0].asNumber().toInt64()), args, 1);
}

Local<Value> LoggerAPI::info(Arguments const& args) {
    // CheckArgsCount(args, 1);
    // CheckArgType(args[0], ValueKind::kString); // any
    return LoggerAPIHelper(endstone::Logger::Level::Info, args);
}

Local<Value> LoggerAPI::warning(Arguments const& args) {
    // CheckArgsCount(args, 1);
    // CheckArgType(args[0], ValueKind::kString); // any
    return LoggerAPIHelper(endstone::Logger::Level::Warning, args);
}

Local<Value> LoggerAPI::error(Arguments const& args) {
    // CheckArgsCount(args, 1);
    // CheckArgType(args[0], ValueKind::kString); // any
    return LoggerAPIHelper(endstone::Logger::Level::Error, args);
}

Local<Value> LoggerAPI::debug(Arguments const& args) {
    // CheckArgsCount(args, 1);
    // CheckArgType(args[0], ValueKind::kString); // any
    return LoggerAPIHelper(endstone::Logger::Level::Debug, args);
}

Local<Value> LoggerAPI::trace(Arguments const& args) {
    // CheckArgsCount(args, 1);
    // CheckArgType(args[0], ValueKind::kString); // any
    return LoggerAPIHelper(endstone::Logger::Level::Trace, args);
}

Local<Value> LoggerAPI::critical(Arguments const& args) {
    // CheckArgsCount(args, 1);
    // CheckArgType(args[0], ValueKind::kString); // any
    return LoggerAPIHelper(endstone::Logger::Level::Critical, args);
}


Local<Value> LoggerAPI::setLevel(Arguments const& args) {
    // CheckArgsCount(args, 1);
    // CheckArgType(args[0], ValueKind::kNumber);
    try {
        auto data = ENGINE_DATA();
        if (data->mPlugin) {
            data->mPlugin->getLogger().setLevel(static_cast<endstone::Logger::Level>(args[0].asNumber().toInt64()));
            return Boolean::newBoolean(true);
        }
        return Boolean::newBoolean(false);
    }
    Catch;
}

Local<Value> LoggerAPI::isEnabledFor(Arguments const& args) {
    // CheckArgsCount(args, 1);
    // CheckArgType(args[0], ValueKind::kNumber);
    try {
        auto data = ENGINE_DATA();
        if (data->mPlugin) {
            return Boolean::newBoolean(data->mPlugin->getLogger().isEnabledFor(
                static_cast<endstone::Logger::Level>(args[0].asNumber().toInt64())
            ));
        }
        return Boolean::newBoolean(false);
    }
    Catch;
}

Local<Value> LoggerAPI::getName(Arguments const& args) {
    try {
        auto data = ENGINE_DATA();
        if (data->mPlugin) {
            return String::newString(data->mPlugin->getLogger().getName());
        }
        return String::newString("");
    }
    Catch;
}


} // namespace jse