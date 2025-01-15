/// <reference path="../../index.d.ts"/>

declare class Permissible {
  toString(): "<Permissible>";

  isOP(): boolean;

  setOp(value: boolean): void;

  isPermissionSet(name: string): boolean;

  isPermissionSet(perm: Permission): boolean;

  hasPermission(name: string): boolean;

  hasPermission(perm: Permission): boolean;

  addAttachment(plugin: Plugin): any;

  addAttachment(plugin: Plugin, name: string, value: boolean): any;

  removeAttachment(attachment:PermissionAttachment): any;

  recalculatePermissions(): void;

  //getEffectivePermissions(): PermissionAttachmentInfo[] // TODO: PermissionAttachmentInfo

  asCommandSender(): CommandSender;
}
