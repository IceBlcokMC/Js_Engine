/// <reference path="../index.d.ts"/>

declare class PermissionAttachment {
    //setRemovalCallback(ex:PermissionRemovedExecutor):void; //TODO: PermissinoRemovedExecutor

    //getRemovalCallback():PermissionRemovedExecutor; //TODO: PermissinoRemovedExecutor

    getPermissible():Permissible;

    getPermissions():any;

    setPermission(name:string,value:boolean):void;

    setPermission(perm:Permission,value:boolean):void;

    unsetPermission(name:string):void;

    unsetPermission(perm:Permission):void;

    remove():boolean;
}