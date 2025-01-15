#pragma once
#include "utils/Defines.h"
#include "utils/Using.h"

namespace jse {

class JSEAPI {
public:
    static METHODS(registerPlugin);

    static METHODS(getSelf);

    static METHODS(debug);

    static METHODS(isLinux);

    static METHODS(isWindows);


    static ClassDefine<void> builder;
};

} // namespace jse
