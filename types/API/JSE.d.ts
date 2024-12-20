/// <reference path="../index.d.ts"/>

declare type PermissionBuilder = {
    [K: string]: {
        /** 权限描述 */
        description: string;
        /** 默认权限 */
        default: Enums.PermissionDefault;
    };
};

// https://endstone.readthedocs.io/en/latest/tutorials/register-commands/#built-in-types
declare type CommandBuilder<P extends PermissionBuilder> = {
    [key: string]: {
        /** 命令描述 */
        description: string;
        /** 命令用法 */
        usages: string[];
        /** 命令权限 */
        permissions: Array<keyof P>;
    };
};

/** JSE提供接口 */
declare class JSE {
    private constructor();

    /**  向引擎注册插件(由引擎向EndStone注册实例) */
    static registerPlugin<P extends PermissionBuilder>(
        /** 插件信息 */
        information: {
            /** 插件名称 */
            name: string;
            /** 插件版本 */
            version: string;
            /** 插件描述 */
            description: string;
            /** 插件加载顺序 */
            load: Enums.PluginLoadOrder;
            /** 插件作者列表 */
            authors: string[];
            /** 插件贡献者列表 */
            contributors: string[];
            /** 插件网站 */
            website: string;
            /** 插件日志标题 */
            prefix: string;
            /** 插件向外提供的API */
            provides: string[];
            /** 插件依赖 */
            depend: string[];
            /** 插件可选依赖 */
            soft_depend: string[];
            /** 获取将此插件视为可选依赖的插件 */
            load_before: string[];
            /** 插件默认命令权限 */
            default_permission: Enums.PermissionDefault;
            /** 权限定义 */
            permissions: P;
            /** 命令列表 */
            commands: CommandBuilder<P>;

            /** 插件加载时回调 */
            onLoad(): void;
            /** 插件启用时回调 */
            onEnable(): void;
            /** 插件禁用时回调 */
            onDisable(): void;
            /** 插件命令执行时回调 */
            onCommand(sender: CommandSender): boolean;
        }
    ): void;

    /** 获取当前插件实例(自身) */
    static getPlugin(): Plugin;

    /** 输出调试信息 */
    static debug(...args: any[]): void;
}