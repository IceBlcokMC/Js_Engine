#pragma once

#include "Engine/Using.h"

namespace jse {
class EndStoneAPI {
public:
    static Local<Value> register_plugin(Arguments const& args); // 注册插件
};

extern ClassDefine<void> EndStoneAPIClass;

} // namespace jse
