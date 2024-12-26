#include "LoggerAPI.h"
#include "APIHelper.h"
#include "Entry.h"
#include "Manager/EngineData.h"
#include "Manager/NodeManager.h"
#include "fmt/args.h"
#include "fmt/format.h"



namespace jse {

ClassDefine<LoggerAPI> LoggerAPI::builder = defineClass<LoggerAPI>("Logger")
                                                .constructor(nullptr)
                                                .instanceFunction("toString", &LoggerAPI::toString)
                                                .instanceFunction("log", &LoggerAPI::log)
                                                .instanceFunction("info", &LoggerAPI::info)
                                                .instanceFunction("warning", &LoggerAPI::warning)
                                                .instanceFunction("error", &LoggerAPI::error)
                                                .instanceFunction("debug", &LoggerAPI::debug)
                                                .instanceFunction("trace", &LoggerAPI::trace)
                                                .instanceFunction("critical", &LoggerAPI::critical)
                                                .instanceFunction("setLevel", &LoggerAPI::setLevel)
                                                .instanceFunction("isEnabledFor", &LoggerAPI::isEnabledFor)
                                                .instanceFunction("getName", &LoggerAPI::getName)
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

Local<Value> LoggerAPI::toString(Arguments const& args) { return String::newString("<Logger>"); }

Local<Value> LoggerAPI::log(Arguments const& args) {
    auto level = magic_enum::enum_cast<endstone::Logger::Level>(args[0].asNumber().toInt64());
    if (!level.has_value()) return Boolean::newBoolean(false);
    return LoggerAPIHelper(*level, args, 1);
}

#define LOGGERAPI_MACRO(FUNC_NAME, LEVEL)                                                                              \
    Local<Value> LoggerAPI::FUNC_NAME(Arguments const& args) {                                                         \
        return LoggerAPIHelper(endstone::Logger::Level::LEVEL, args);                                                  \
    }

LOGGERAPI_MACRO(info, Info);
LOGGERAPI_MACRO(warning, Warning);
LOGGERAPI_MACRO(error, Error);
LOGGERAPI_MACRO(debug, Debug);
LOGGERAPI_MACRO(trace, Trace);
LOGGERAPI_MACRO(critical, Critical);

#undef LOGGERAPI_MACRO

Local<Value> LoggerAPI::setLevel(Arguments const& args) {
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