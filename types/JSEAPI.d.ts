declare namespace Enums {
  enum PermissionDefault {
    True,
    False,
    Operator,
    NotOperator
  }

  enum PluginLoadOrder {
    Startup,
    PostWorld
  }
}

declare type PermissionBuilder = {
  [K: string]: {
    description: string;
    default: Enums.PermissionDefault;
  };
};

// https://endstone.readthedocs.io/en/latest/tutorials/register-commands/#built-in-types
declare type CommandBuilder<P extends PermissionBuilder> = {
  [key: string]: {
    description: string;
    usages: string[];
    permissions: Array<keyof P>;
  };
};

declare interface JsPluginBuilder<
  P extends PermissionBuilder = PermissionBuilder
> {
  name: string;
  version: string;
  description: string;
  load: Enums.PluginLoadOrder;
  authors: string[];
  contributors: string[];
  website: string;
  prefix: string;
  provides: string[];
  depend: string[];
  soft_depend: string[];
  load_before: string[];
  default_permission: Enums.PermissionDefault;
  permissions: P;
  commands: CommandBuilder<P>;

  onLoad(): void;
  onEnable(): void;
  onDisable(): void;
  onCommand(): boolean; // TODO
}

declare class JSE {
  /**
   * 向引擎注册插件（由引擎向EndStone注册实例）
   * @param information 插件信息
   */
  static registerPlugin<P extends PermissionBuilder>(
    information: JsPluginBuilder<P>
  ): void;

  /**
   * 获取当前插件实例(自身)
   */
  static getPlugin(): Plugin;

  static debug(...args: any[]): void;
}
