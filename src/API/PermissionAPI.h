#pragma once
#include "API/APIHelper.h"
#include "Utils/Defines.h"
#include "Utils/Using.h"
#include "endstone/permissions/permission.h"


namespace jse {


class PermissionAPI : public ScriptClass {
    endstone::Permission* mPermission;

public:
    explicit PermissionAPI(endstone::Permission* permission)
    : ScriptClass(ScriptClass::ConstructFromCpp<PermissionAPI>{}),
      mPermission(permission) {}

    static Local<Object> newPermissionAPI(endstone::Permission* permission) {
        return (new PermissionAPI{permission})->getScriptObject();
    }

    endstone::Permission* get() { return mPermission; }

    METHODS(toString);
    METHODS(getName);
    METHODS(getChildren);
    METHODS(getDefault);
    METHODS(setDefault);
    METHODS(getDescription);
    METHODS(setDescription);
    METHODS(getPermissibles);
    METHODS(recalculatePermissibles);
    METHODS(addParent);
    METHODS(init);
};


} // namespace jse