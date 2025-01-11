/// <reference path="../index.d.ts"/>

declare class CommandSender {
    toString(): "<CommandSender>";

    // asCommandSender():any // depreciated

    //asConsole(): ConsoleCommandSender // TODO: ConsoleAPI

    asActor(): Actor // TODO: ActorAPI

    asPlayer(): Player|undefined;

    /** 返回正常消息 */
    sendMessage(...args: any[]): void;

    /** 返回错误消息 */
    sendErrorMessage(...args: any[]): void;

    // getServer(): Server // TODO: ServerAPI

    getName(): string;

}