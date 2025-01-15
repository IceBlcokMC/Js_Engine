/// <reference path="../../index.d.ts"/>

declare class Command {
    toString(): "<Command>";

    execute(sender: CommandSender, args: string[]): boolean;

    getName(): string;

    setName(name: string): void;

    getDescription(): string;

    setDescription(description: string): void;

    getAliases(): string[];

    setAliases(...aliases: string[]): void;

    getUsages(): string[];

    setUsages(...usages: string[]): void;

    getPermissions(): string[];

    setPermissions(...permissions: string[]): void;

    testPermission(target: CommandSender): boolean;

    testPermissionSilently(target: CommandSender): boolean;

    // registerTo(): any; // TODO: CommandMap

    // unregisterFrom(): any; // TODO: CommandMap

    isRegistered(): boolean;

    // asPluginCommand(): any; // TODO: PluginCommand
}
