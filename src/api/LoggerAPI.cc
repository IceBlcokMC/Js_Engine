#include "api/LoggerAPI.h"
#include "api/APIHelper.h"
#include "manager/EngineData.h"
#include <cstddef>

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

void LoggerAPIHelper(endstone::Logger* logger, endstone::Logger::Level level, string const& message) {
    try {
        if (logger) {
            logger->log(level, message);
        }
    }
    CatchNotReturn;
}

void LoggerAPIHelper(endstone::Logger* logger, endstone::Logger::Level level, Arguments const& args, int start = 0) {
    try {
        std::ostringstream oss;
        for (size_t i = start; i < args.size(); ++i) ToString(args[i], oss);
        LoggerAPIHelper(logger, level, oss.str());
    }
    CatchNotReturn;
}

Local<Value> LoggerAPI::toString(Arguments const& /* args */) { return String::newString("<Logger>"); }

Local<Value> LoggerAPI::log(Arguments const& args) {
    auto level = magic_enum::enum_cast<endstone::Logger::Level>(args[0].asNumber().toInt64());
    if (!level.has_value()) return Boolean::newBoolean(false);
    LoggerAPIHelper(get(), *level, args, 1);
    return Local<Value>();
}

#define LOGGERAPI_MACRO(FUNC_NAME, LEVEL)                                                                              \
    Local<Value> LoggerAPI::FUNC_NAME(Arguments const& args) {                                                         \
        LoggerAPIHelper(get(), endstone::Logger::Level::LEVEL, args);                                                  \
        return Local<Value>();                                                                                         \
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
        if (get()) {
            get()->setLevel(static_cast<endstone::Logger::Level>(args[0].asNumber().toInt64()));
        }
        return Local<Value>();
    }
    Catch;
}

Local<Value> LoggerAPI::isEnabledFor(Arguments const& args) {
    try {
        if (!get()) {
            return Boolean::newBoolean(false);
        }
        return Boolean::newBoolean(get()->isEnabledFor(static_cast<endstone::Logger::Level>(args[0].asNumber().toInt64()
        )));
    }
    Catch;
}

Local<Value> LoggerAPI::getName(Arguments const& /* args */) {
    try {
        if (!get()) {
            return Local<Value>();
        }
        return String::newString(get()->getName());
    }
    Catch;
}

} // namespace jse