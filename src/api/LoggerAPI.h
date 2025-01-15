#pragma once
#include "endstone/logger.h"
#include "utils/Defines.h"
#include "utils/Using.h"

namespace jse {

class LoggerAPI : public ScriptClass {
    endstone::Logger* mLogger;

public:
    explicit LoggerAPI(endstone::Logger* logger)
    : ScriptClass(ScriptClass::ConstructFromCpp<LoggerAPI>{}),
      mLogger(logger) {};

    static Local<Object> newLoggerAPI(endstone::Logger* logger) { return (new LoggerAPI(logger))->getScriptObject(); }

    endstone::Logger* get() { return mLogger; }

public:
    METHODS(toString);

    METHODS(log);
    METHODS(info);
    METHODS(warning);
    METHODS(error);
    METHODS(debug);
    METHODS(critical);
    METHODS(trace);

    METHODS(setLevel);
    METHODS(isEnabledFor);
    METHODS(getName);


    static ClassDefine<LoggerAPI> builder;
};


} // namespace jse