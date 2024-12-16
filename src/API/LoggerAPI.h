#pragma once
#include "Engine/Using.h"

namespace jse {


class LoggerAPI : public ScriptClass {
public:
    explicit LoggerAPI() : ScriptClass(ScriptClass::ConstructFromCpp<LoggerAPI>{}){};

    static Local<Object> newLoggerAPI() { return (new LoggerAPI())->getScriptObject(); }

public:
    Local<Value> log(Arguments const& args);
    Local<Value> info(Arguments const& args);
    Local<Value> warning(Arguments const& args);
    Local<Value> error(Arguments const& args);
    Local<Value> debug(Arguments const& args);
    Local<Value> critical(Arguments const& args);
    Local<Value> trace(Arguments const& args);

    Local<Value> setLevel(Arguments const& args);
    Local<Value> isEnabledFor(Arguments const& args);
    Local<Value> getName(Arguments const& args);
};

extern ClassDefine<LoggerAPI> LoggerAPIClass;


} // namespace jse