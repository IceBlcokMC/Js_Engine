#pragma once
#include "Utils/Defines.h"
#include "Utils/Using.h"

namespace jse {

class LoggerAPI : public ScriptClass {
public:
    explicit LoggerAPI() : ScriptClass(ScriptClass::ConstructFromCpp<LoggerAPI>{}){};

    static Local<Object> newLoggerAPI() { return (new LoggerAPI())->getScriptObject(); }

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