#pragma once

#include "Utils/Using.h"

namespace jse {

class JSEAPI {
public:
    static Local<Value> registerPlugin(Arguments const& args); // 注册插件

    static Local<Value> getPlugin(Arguments const& args);

    static Local<Value> debug(Arguments const& args);


    static ClassDefine<void> builder;
};

} // namespace jse
