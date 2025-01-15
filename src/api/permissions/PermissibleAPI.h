#pragma once
#include "Utils/Defines.h"
#include "Utils/Using.h"
#include <endstone/permissions/permissible.h>

namespace jse {

class PermissibleAPI : public ScriptClass {
    endstone::Permissible* mPermissible;

public:
    template <typename T>
    explicit PermissibleAPI(endstone::Permissible* permissible, ScriptClass::ConstructFromCpp<T> tag)
    : ScriptClass(tag),
      mPermissible(permissible) {}

    explicit PermissibleAPI(endstone::Permissible* permissible)
    : ScriptClass(ScriptClass::ConstructFromCpp<PermissibleAPI>{}),
      mPermissible(permissible) {}

    static Local<Object> newPermissibleAPI(endstone::Permissible* permissible) {
        return (new PermissibleAPI(permissible))->getScriptObject();
    }

    METHODS(toString);
    METHODS(isOP);
    METHODS(setOp);
    METHODS(isPermissionSet);
    METHODS(hasPermission);
    METHODS(addAttachment);
    METHODS(removeAttachment);
    METHODS(recalculatePermissions);
    METHODS(getEffectivePermissions);
    METHODS(asCommandSender);


    static ClassDefine<PermissibleAPI> builder;
};


} // namespace jse