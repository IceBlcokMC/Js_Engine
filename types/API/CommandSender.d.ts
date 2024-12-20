/// <reference path="../index.d.ts"/>

declare class CommandSender extends Permissible {
    toString(): string

    // asCommandSender():any // depreciated

    // asConsole(): any // TODO: ConsoleAPI

    // asActor(): any // TODO: ActorAPI

    // asPlayer(): any // TODO: PlayerAPI

    sendMessage(...args: any[]): void

    sendErrorMessage(...args: any[]): void

    // getServer(): any // TODO: ServerAPI

    getName(): string
}