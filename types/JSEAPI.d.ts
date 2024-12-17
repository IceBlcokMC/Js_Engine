/**
 * permission_default.h
 * @default Operator
 */
declare type PermissionDefault = "True" | "False" | "Operator" | "NotOperator";

/**
 * plugin_load_order.h
 * Represents the order in which a plugin should be initialized and enabled.
 * @default PostWorld
 */
declare type PluginLoadOrder =
  /**
   * Indicates that the plugin will be loaded at startup
   */
  | "Startup"
  /**
   * Indicates that the plugin will be loaded after the first/default world
   * was created
   */
  | "PostWorld";

declare type CommandBuilder = {
  [key: string]: {
    description: string;
    usages: string[];
    permissions: string[];
  };
};
declare type PermissionBuilder = {
  [key: string]: {
    description: string;
    default: PermissionDefault;
  };
};

declare interface JsPluginBuilder {
  name: string;
  version: string;
  description: string;
  load: PluginLoadOrder;
  authors: string[];
  contributors: string[];
  website: string;
  prefix: string;
  provides: string[];
  depend: string[];
  soft_depend: string[];
  load_before: string[];
  default_permission: PermissionDefault;
  commands: CommandBuilder;
  permissions: PermissionBuilder;

  /**
   * @deprecated
   */
  onLoad(): void;
  onEnable(): void;
  onDisable(): void;
}

declare class JSE {
  /**
   * 向引擎注册插件（由引擎向EndStone注册实例）
   * @param information 插件信息
   */
  static registerPlugin(information: JsPluginBuilder): void;

  /**
   * 获取当前插件实例(自身)
   */
  static getPlugin(): Plugin;

  static debug(...args: any[]): void;
}
