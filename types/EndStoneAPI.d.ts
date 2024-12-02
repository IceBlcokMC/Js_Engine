declare type PluginInformation = {
  name: string;
  version: string;
  description: string;
};

declare class JSE_EndStone {
  static registerPlugin(information: PluginInformation): void;
}

declare namespace globalThis {
  /**
   * 插件加载
   * @returns
   */
  declare function onLoad(): void;

  /**
   * 插件开启
   * @returns
   */
  declare function onEnable(): void;

  /**
   * 插件关闭
   * @returns
   */
  declare function onDisable(): void;
}
