/// <reference path="../../index.d.ts"/>

declare class Permissible {
    toString(): "<Permissible>";

    isOP(): boolean;

    setOp(value: boolean): void;

    isPermissionSet(name: string): boolean;

    isPermissionSet(perm: Permission): boolean;

    hasPermission(name: string): boolean;

    hasPermission(perm: Permission): boolean;

    /** 此接口执行失败会抛出异常 */
    // addAttachment(plugin: Plugin): any; // TODO: PermissionAttachment

    /** 此接口执行失败会抛出异常 */
    // addAttachment(plugin: Plugin, name: string, value: boolean): any; // TODO: PermissionAttachment

    // removeAttachment(attachment: PermissionAttachment): any; // TODO: PermissionAttachment

    recalculatePermissions(): void;

    //getEffectivePermissions(): PermissionAttachmentInfo[] // TODO: PermissionAttachmentInfo

    asCommandSender(): CommandSender;
}
