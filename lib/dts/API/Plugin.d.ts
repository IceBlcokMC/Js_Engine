/// <reference path="../index.d.ts"/>

/** 插件实例 */
interface Plugin { // 保证正常补全
    toString(): "<Plugin>";

    /** 获取插件相关信息 */
    getDescription(): PluginDescriptionAPI;

    /** 调用插件注册的onLoad函数 */
    onLoad(): void;

    /** 调用插件注册的onEnable函数 */
    onEnable(): void;

    /** 调用插件注册的onDisable函数 */
    onDisable(): void;

    /** 获取插件的日志输出 */
    getLogger(): Logger;

    /** 插件是否已启用 */
    isEnabled(): boolean;

    // getPluginLoader(): any; // TODO

    // getServer(): any; // TODO

    /** 获取插件名字 */
    getName(): string;

    // getCommand(): any; // TODO

    /** 获取插件的数据存储目录 */
    getDataFolder(): string;

    // registerEvent(): any; // TODO
}