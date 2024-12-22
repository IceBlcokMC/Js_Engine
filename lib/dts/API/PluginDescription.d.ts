/// <reference path="../index.d.ts"/>

/** 插件相关信息 */
declare class PluginDescriptionAPI {
    private constructor();

    toString(): "<PluginDescriptionAPI>";

    /** 获取插件名字 */
    getName(): string;
  
    /** 获取插件版本 */
    getVersion(): string;
  
    /** 获取插件完整名字(名字+版本) */
    getFullName(): string;
  
    /** 获取插件所需API版本 */
    getAPIVersion(): string;
  
    /** 获取插件描述 */
    getDescription(): string;
  
    /** 获取插件加载顺序 */
    getLoad(): Enums.PluginLoadOrder;
  
    /** 获取插件作者列表 */
    getAuthors(): string[];
  
    /** 获取插件贡献者列表 */
    getContributors(): string[];
  
    /** 获取插件网站 */
    getWebsite(): string;
  
    /** 获取插件日志标题 */
    getPrefix(): string;
  
    /** 获取本插件向外提供的API */
    getProvides(): string[];
  
    /** 获取插件依赖 */
    getDepend(): string[];
  
    /** 获取插件可选依赖 */
    getSoftDepend(): string[];
  
    /** 获取将此插件视为可选依赖的插件 */
    getLoadBefore(): string[];
  
    /** 获取插件默认命令权限 */
    getDefaultPermission(): Enums.PermissionDefault;
  
    // getCommands(): any;
  
    // getPermissions(): any;
  }