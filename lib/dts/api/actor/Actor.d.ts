/// <reference path="../../index.d.ts"/>

/** 实体 */
declare class Actor extends CommandSender {
    toString(): "<Actor>" | string;

    /** 获取实体命名空间ID */
    getType(): string;

    /** 获取实体RuntimeId */
    getRuntimeId(): number;

    //getLocation():Location;

    // getVelocity(): number[];

    /** 实体是否在地面上 */
    isOnGround(): boolean;

    /** 实体是否在水中 */
    isInWater(): boolean;

    /** 实体是否在岩浆中 */
    isInLava(): boolean;

    //getLevel():Level;

    //getDimension():Dimension;

    // setRotation(yaw: number, pitch: number): void;

    //teleport(location:Location):void; //TODO Location

    /** 获取实体的UniqueId */
    getId(): number;

    /** 实体是否死亡 */
    isDead(): boolean;

    /** 获取实体当前血量 */
    getHealth(): number;

    /** 设置实体当前血量 */
    setHealth(health: number): void;

    /** 获取实体最大血量 */
    getMaxHealth(): number;

    /** 获取实体的所有标签 */
    getScoreboardTags(): string[];

    /** 给实体添加标签 */
    addScoreboardTag(
        /** 标签 */
        tag: string
    ): boolean;

    /** 删除实体标签 */
    removeScoreboardTag(
        /** 标签 */
        tag: string
    ): boolean;

    /** 实体能否显示名字标签 */
    isNameTagVisible(): boolean;

    /** 设置实体名字标签是否显示 */
    setNameTagVisible(visible: string): void;

    /** 实体名字标签是否总是显示 */
    isNameTagAlwaysVisible(): boolean;

    /** 设置实体名字标签是否总是显示 */
    setNameTagAlwaysVisible(
        /** 是否总是显示 */
        visible: string
    ): boolean;

    /** 获取实体名字标签 */
    getNameTag(): string;

    /** 设置实体名字标签 */
    setNameTag(name: string): void;

    getScoreTag(): string;

    setScoreTag(score: string): void;
}
