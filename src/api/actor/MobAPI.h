#pragma once
#include "api/actor/ActorAPI.h"
#include "utils/Defines.h"
#include "utils/Using.h"
#include <endstone/actor/mob.h>

namespace jse {

class MobAPI : public ActorAPI {
    endstone::Mob* mMob;

public:
    template <typename T>
    explicit MobAPI(endstone::Mob* mob, ScriptClass::ConstructFromCpp<T> tag) : ActorAPI(mob, tag),
                                                                                mMob(mob) {}

    explicit MobAPI(endstone::Mob* mob) : ActorAPI(mob, ScriptClass::ConstructFromCpp<MobAPI>{}), mMob(mob) {}

    static Local<Object> newMobAPI(endstone::Mob* mob) { return (new MobAPI(mob))->getScriptObject(); }

    endstone::Mob* get() { return mMob; }

    METHODS(toString);
    METHODS(isGliding);

    static ClassDefine<MobAPI> builder;
};


} // namespace jse