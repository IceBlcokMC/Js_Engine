/// <reference path="../index.d.ts"/>

declare namespace Enums {
    /** 插件加载顺序 */
    enum PluginLoadOrder {
        /** 在启动时加载 */
        Startup = 0,
        /** 在世界加载后加载 */
        PostWorld = 1
    }
}