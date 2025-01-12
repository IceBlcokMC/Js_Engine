/// <reference path="../index.d.ts"/>

declare class Server{
    getName():string;

    getVersion():string;

    getMinecraftVersion():string;

    getLogger():Logger;

    getLanguage():Language;

    getPluginManager():PluginManager;

    getPluginCommand():PluginCommand;

    //getCommandSender():ConsoleCommandSender; //TODO: ConsoleCommandSender

    dispatchCommand(sender:CommandSender,command_line:string):boolean;

    //getScheduler():Scheduler;

    //getLevel():Level;

    getOnlinePlayers():Player;

    getMaxPlayer():number;

    //getPlayer(uuid:UUID):Player; //TODO: UUID

    getOnlineMode():boolean;

    getPlayer(name:string):Player;

    shutdown():void;

    reload():void;
    
    reloadData():void;

    //broadcast(message:Message,permission:string):void;

    //broadcastMessage(message:Message):void;

    //broadcastMessage(format,args):void;

    isPrimaryThread():boolean;

    //getScoreboard():Scoreboard;

    //createScoreboard()

    getCurrentMillisecondsPerTick():number;

    getAverageMillisecondsPerTick():number;

    getCurrentTicksPerSecond():number;

    getAverageTicksPerSecond():number;

    getCurrentTickUsage():number;

    getAverageTickUsage():number;

    //getStartTime()

    //createBossBar(title:string,color:BarColor,style:BarStyle)

    
    //createBossBar(title:string,color:BarColor,style:BarStyle,flags)
    
    //createBlockData(type:string)

    //createBlockData(type:string,block_states:BlockStates)

    //getBanList():PlayerBanList;

    //static BroadcastChannelAdmin:string;//="endstone.broadcast.admin"

    //static BroadcastChannelUser:string;//="endstone.broadcast.admin"
}