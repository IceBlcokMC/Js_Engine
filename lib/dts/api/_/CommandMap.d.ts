/// <reference path="../index.d.ts"/>

declare class CommandMap {
    registerCommand(command:Command):boolean;

    dispatch(sender:CommandSender,command_line:string):boolean;

    clearCommands():void;

    getCommand(name:string):Command
}