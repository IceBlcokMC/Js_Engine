/// <reference path="../index.d.ts"/>
declare class Actor{
    toString():string;

    getType():string;

    getRuntimeId():number;

    //getLocation():Location;

    getVelocity():number[];

    isOnGround():boolean;

    isInWater():boolean;

    isInLava():boolean;

    //getLevel():Level;

    //getDimension():Dimension;

    setRotation(yaw:number,pitch:number):void;

    //teleport(location:Location):void; //TODO Location

    getId():number;

    isDead():boolean;

    getHealth():number;

    setHealth(health:number):void;

    getMaxHealth():number;

    getScoreboardTags():string[];

    addScoreboardTag(tag:string):boolean;

    removeScoreboardTag(tag:string):boolean;

    isNameTagVisible():boolean;

    setNameTagVisible(visible:string):void;

    isNameTagAlwaysVisible():boolean;

    setNameTagAlwaysVisible(visible:string):boolean;

    getNameTag():string;

    setNameTag(name:string):void;

    getScoreTag():string;

    setScoreTag(score:string):void;

}