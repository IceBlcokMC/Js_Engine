/// <reference path="../../index.d.ts"/>

declare class Permission {
    toString(): "<Permission>";

    getName(): string;

    getChildren(): { [k: string]: boolean };

    getDefault(): Enums.PermissionDefault;

    setDefault(default_: Enums.PermissionDefault): void;

    getDescription(): string;

    setDescription(description: string): void;

    getPermissibles(): Permissible[];

    recalculatePermissibles(): void;

    addParent(name: string, value: boolean): Permission;

    addParent(perm: Permission, value: boolean): void;

    // init(): any; // TODO: PluginManager
}
