#pragma once
#include "Engine/Using.h"

namespace jse {


class LoggerAPI {
public:
    static Local<Value> log(Arguments const& args);
    static Local<Value> info(Arguments const& args);
    static Local<Value> warning(Arguments const& args);
    static Local<Value> error(Arguments const& args);
    static Local<Value> debug(Arguments const& args);
    static Local<Value> critical(Arguments const& args);
    static Local<Value> trace(Arguments const& args);

    static Local<Value> setLevel(Arguments const& args);
    static Local<Value> isEnabledFor(Arguments const& args);
    static Local<Value> getName(Arguments const& args);
};

extern ClassDefine<void> LoggerAPIClass;


} // namespace jse