/// <reference path="../index.d.ts"/>

declare class PluginManager {
    //registerLoader(loader):void;

    getPlugin(name:string):Plugin;

    getPlugins():Plugin[];

    isPluginEnabled(name:string):boolean;

    isPluginEnabled(plugin:Plugin):boolean;
    /**
     * 从指定的文件加载插件    
     * 文件对于已经启用的插件接口必须是有效的
     * @param file 内含要加载的插件的文件
     * @return 加载成功时返回插件实例，否则返回undefined
     */
    loadPlugin(file:string):Plugin|undefined;

    loadPluigns(directory:string):Plugin[];

    loadPlugins(files:string[]):Plugin[];

    enablePlugin(plugin:Plugin):void;
    /**
     * 启用所有已加载的插件
     */
    enablePlugins():void;

    disablePlugin(plugin:Plugin):void;
    /**
     * 关闭所有已加载的插件
     */
    disablePlugins():void;
    
    clearPlugins():void;

    callEvent(event:Event):void;

    //registerEvent(event:string,executor:(event:Event)=>void,priority:EventPriority,plugin:Plugin,ignore_cancelled:boolean):any;

    getPermission(name:string):Permission;

    //addPermission()

    removePermission(perm:Permission):void;

    removePermission(name:string):void;

    recalculatePermissionDefaults(perm:Permission):void;

    subscribeToPermission(permission:string,permissible:Permissible):void

    unsubscribeFromPermission(permission:string,permissible:Permissible):void;

    subscribeToDefaultPerms(op:boolean,permissible:Permissible):void;

    unsubscribeFromDefaultPerms(op:boolean,permissible:Permissible):void;

    //getDefaultPermSubscriptions(op:boolean)

    //getPermissions()
}