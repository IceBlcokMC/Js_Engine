#include "api/permissions/PermissionAPI.h"
#include "api/APIHelper.h"
#include "api/permissions/PermissibleAPI.h"
#include "utils/Convert.h"
#include "utils/Defines.h"
#include <endstone/permissions/permission_default.h>

namespace jse {

Local<Value> PermissionAPI::toString(Arguments const& /* args */) { return ConvertToScriptX("Permission"); }

Local<Value> PermissionAPI::getName(Arguments const& /* args */) {
    try {
        return ConvertToScriptX(this->mPermission->getName());
    }
    Catch;
}

Local<Value> PermissionAPI::getChildren(Arguments const& /* args */) {
    try {
        return ConvertToScriptX(this->mPermission->getChildren());
    }
    Catch;
}

Local<Value> PermissionAPI::getDefault(Arguments const& /* args */) {
    try {
        return ConvertToScriptX(this->mPermission->getDefault());
    }
    Catch;
}

Local<Value> PermissionAPI::setDefault(Arguments const& args) {
    try {
        this->mPermission->setDefault(ConvertFromScriptX<endstone::PermissionDefault>(args[0]));
        return Local<Value>();
    }
    Catch;
}

Local<Value> PermissionAPI::getDescription(Arguments const& /* args */) {
    try {
        return ConvertToScriptX(this->mPermission->getDescription());
    }
    Catch;
}

Local<Value> PermissionAPI::setDescription(Arguments const& args) {
    try {
        this->mPermission->setDescription(args[0].asString().toString());
        return Local<Value>();
    }
    Catch;
}

Local<Value> PermissionAPI::getPermissibles(Arguments const& /* args */) {
    try {
        auto perms = this->mPermission->getPermissibles();
        auto array = Array::newArray(perms.size());
        for (auto p : perms) {
            array.add(PermissibleAPI::newPermissibleAPI(p));
        }
        return array;
    }
    Catch;
}

Local<Value> PermissionAPI::recalculatePermissibles(Arguments const& /* args */) {
    try {
        this->mPermission->recalculatePermissibles();
        return Local<Value>();
    }
    Catch;
}

Local<Value> PermissionAPI::addParent(Arguments const& args) {
    try {
        if (args[0].isString()) {
            if (auto val = this->mPermission->addParent(args[0].asString().toString(), args[1].asBoolean().value())) {
                return PermissionAPI::newPermissionAPI(val);
            }
        } else if (IsInstanceOf<PermissionAPI>(args[0])) {
            this->mPermission->addParent(*GetScriptClass(PermissionAPI, args[0])->get(), args[1].asBoolean().value());
        }
        return Local<Value>();
    }
    Catch;
}

Local<Value> PermissionAPI::init(Arguments const& /* args */) {
    try {
        // TODO: PluginManager
    }
    Catch;
}


} // namespace jse