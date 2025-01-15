/// <reference path="../index.d.ts"/>

declare class PluginCommand{
    execute(sender:CommandSender,args:string[]):boolean;

    getName():string;

    setName(name:string):void;

    getDescription():string;

    setDescription(description:string):void;

    getAliases():string[];

    getUsages():string[];

    setUsages(...usages:any[]):void;

    getPermissions():string[];

    setPermissions(...permissions:Permission[]):void;

    testPermission(target:CommandSender):boolean;

    testPermissionSilently(target:CommandSender):boolean;

    registerTo(command_map:CommandMap):boolean;

    unregisterFrom(command_map:CommandMap):boolean;

    asPluginCommand():PluginCommand;
}