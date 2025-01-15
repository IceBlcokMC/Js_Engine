/// <reference path="../../index.d.ts"/>

/** 命令来源 */
declare class CommandSender {
    toString(): string | "<CommandSender>";

    /** 转成命令发送者 */
    asCommandSender(): CommandSender | undefined;

    // asConsole(): ConsoleCommandSender // TODO: ConsoleAPI

    /** 转成实体 */
    asActor(): Actor | undefined;

    /** 转成玩家 */
    asPlayer(): Player | undefined;

    /** 返回正常消息 */
    sendMessage(...args: any[]): void;

    /** 返回错误消息 */
    sendErrorMessage(...args: any[]): void;

    // getServer(): Server // TODO: ServerAPI

    getName(): string;
}
