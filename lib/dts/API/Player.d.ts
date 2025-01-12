/// <reference path="../index.d.ts"/>

declare class Player{
    toString():string;

    getUniqueId():string;

    getXuid():string;

    getAddress():string;

    sendPopup(message:string):void;

    sendTip(message:string):void;

    sendToast(title:string,content:string):void;

    kick(message:string):void;

    giveExp(amount:number):void;

    giveExpLevels(amount:number):void;

    getExpProgress():number;

    setExpProgress(progress:number):void;

    getExpLevel():number;

    setExpLevel(level:number):void;

    getTotalExp():number;

    getAllowFlight():boolean;

    setAllowFlight(flight:boolean):void;

    isFlying():boolean;

    setFlying(value:boolean):void;

    getFlySpeed():number;

    setFlySpeed(value:number):void;

    getWalkSpeed():number;

    setWalkSpeed(value:number):void;

    //getScoreboard():Scoreboard; //TODO Scoreboard

    //setScoreboard(scordboard:Scoreboard):void;//TODO Scoreboard

    sendTitle(title:string,subtitle:string):void;

    sendTitle(title:string,subtitle:string,fade_in:number,stay:number,fade_out:number):void;

    resetTitle():void;

    //spawnParticle(name:string,location:Location); //TODO Location

    spawnParticle(name:string,x:number,y:number,z:number):void; 

    spawnParticle(name:string,x:number,y:number,z:number,molang_variables_json?:string):void;

    getPing():number;

    updateCommands():void;

    performCommand(command:string):void;

    //getGameMode():GameMode; //TODO GameMode

    //setGameMode(mode:GameMode):void; //TODO GameMode

    //getInventory():PlayerInventory; //TODO PlayerInventory

    getLocale():string;

    getDeviceOS():string;

    getDeviceId():string;

    getGameVersion():string;

    //getSkin():Skin; //TODO Skin

    transfer(host:string,port:number):void;

    //sendForm(form:FormVariant); //TODO FormVariant

    closeForm():void;

    //closeForm(packet:Packet); //TODO Packet
}