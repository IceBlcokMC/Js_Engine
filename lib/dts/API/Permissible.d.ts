/// <reference path="../index.d.ts"/>

declare class Permissible {
  toString(): "<Permissible>";

  isOP(): boolean;

  setOp(value: boolean): void;

  isPermissionSet(name: string): boolean;

  isPermissionSet(perm: Permission): boolean;

  hasPermission(name: string): boolean;

  hasPermission(perm: Permission): boolean;

  // addAttachment(plugin: Plugin): Result<PermissionAttachment> // TODO: PermissionAttachment

  // addAttachment(plugin: Plugin, name: string, value: boolean): Result<PermissionAttachment> // TODO: PermissionAttachment

  // removeAttachment(attachment:PermissionAttachment): Result<void> // TODO: PermissionAttachment

  recalculatePermissions(): void;

  // getEffectivePermissions(): PermissionAttachmentInfo[] // TODO: PermissionAttachmentInfo

  // asCommandSender(): CommandSender // TODO: CommandSender
}
