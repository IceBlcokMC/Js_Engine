/// <reference path="../index.d.ts"/>

declare class Permissible {
    toString(): "<Permissible>";

    isOP(): boolean;

    setOp(value: boolean): void;

    isPermissionSet(name: string): boolean;
    // isPermissionSet(perm: Permission): boolean // TODO

    hasPermission(name: string): boolean;
    // hasPermission(perm: Permission): boolean // TODO

    // addAttachment(plugin: Plugin): any // TODO
    // addAttachment(plugin: Plugin, name: string, value: boolean): any // TODO

    // removeAttachment(): any // TODO

    recalculatePermissions(): void;

    // getEffectivePermissions(): any // TODO

    // asCommandSender(): any // TODO
}
