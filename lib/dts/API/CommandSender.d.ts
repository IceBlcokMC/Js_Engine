/// <reference path="../index.d.ts"/>

declare class CommandSender {
    toString(): "<CommandSender>";

    // asCommandSender():any // depreciated

    // asConsole(): any // TODO: ConsoleAPI

    // asActor(): any // TODO: ActorAPI

    // asPlayer(): any // TODO: PlayerAPI

    /** 返回正常消息 */
    sendMessage(...args: any[]): void;

    /** 返回错误消息 */
    sendErrorMessage(...args: any[]): void;

    // getServer(): any // TODO: ServerAPI

    getName(): string;
}