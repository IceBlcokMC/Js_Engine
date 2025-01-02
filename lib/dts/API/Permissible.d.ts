/// <reference path="../index.d.ts"/>

declare class Permissible {
  toString(): "<Permissible>";

  isOP(): boolean;

  setOp(value: boolean): void;

  isPermissionSet(name: string): boolean;

  isPermissionSet(perm: Permission): boolean;

  hasPermission(name: string): boolean;

  hasPermission(perm: Permission): boolean;

  // addAttachment(plugin: Plugin): any // TODO: PermissionAttachment
  // addAttachment(plugin: Plugin, name: string, value: boolean): any // TODO: PermissionAttachment

  // removeAttachment(): any // TODO: PermissionAttachment

  recalculatePermissions(): void;

  // getEffectivePermissions(): any // TODO: PermissionAttachmentInfo

  // asCommandSender(): any // TODO: CommandSender
}
