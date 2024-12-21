#pragma once
#include "Utils/Defines.h"
#include "Utils/Using.h"

namespace jse {

class JSEAPI {
public:
    static METHODS(registerPlugin);

    static METHODS(getPlugin);

    static METHODS(debug);

    static METHODS(isLinux);

    static METHODS(isWindows);


    static ClassDefine<void> builder;
};

} // namespace jse
