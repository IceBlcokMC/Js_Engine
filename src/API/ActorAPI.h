#pragma once

#include "API/CommandSenderAPI.h"
#include "Utils/Defines.h"
#include "Utils/Using.h"
#include "endstone/actor/actor.h"

namespace jse {

class ActorAPI : public CommandSenderAPI {
    endstone::Actor* mActor;

public:
    template <typename T>
    explicit ActorAPI(endstone::Actor* actor, ScriptClass::ConstructFromCpp<T> tag)
    : CommandSenderAPI(actor, tag),
      mActor(actor) {}

    explicit ActorAPI(endstone::Actor* actor)
    : CommandSenderAPI(actor, ScriptClass::ConstructFromCpp<ActorAPI>{}),
      mActor(actor) {}

    static Local<Object> newActorAPI(endstone::Actor* actor) { return (new ActorAPI(actor))->getScriptObject(); }

    endstone::Actor* get() { return mActor; }

    METHODS(toString);
    METHODS(getType);
    METHODS(getRuntimeId);
    METHODS(getLocation); // todo Location类没写
    METHODS(getVelocity); // todo Velocity类没写
    METHODS(isOnGround);
    METHODS(isInWater);
    METHODS(isInLava);
    METHODS(getLevel);     // todo Level类没写
    METHODS(getDimension); // todo Dimension类没写
    METHODS(setRotation);  // todo Rotation类没写
    METHODS(teleport);     // todo Location类没写
    METHODS(getId);
    METHODS(isDead);
    METHODS(getHealth);
    METHODS(setHealth);
    METHODS(getMaxHealth);
    METHODS(getScoreboardTags);
    METHODS(addScoreboardTag);
    METHODS(removeScoreboardTag);
    METHODS(isNameTagVisible);
    METHODS(setNameTagVisible);
    METHODS(isNameTagAlwaysVisible);
    METHODS(setNameTagAlwaysVisible);
    METHODS(getNameTag);
    METHODS(setNameTag);
    METHODS(getScoreTag);
    METHODS(setScoreTag);

    static ClassDefine<ActorAPI> builder;
};


} // namespace jse