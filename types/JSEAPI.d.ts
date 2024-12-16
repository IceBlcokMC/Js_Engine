
declare interface JSE_Plugin_Register {
  name: string;
  version: string;
  description: string;
  load: "PostWorld" | "Startup"; // default: PostWorld
  authors: string[];
  contributors: string[];
  website: string;
  prefix: string;
  provides: string[];
  depend: string[];
  soft_depend: string[];
  load_before: string[];
  default_permission: "Operator" | "True" | "False" | "NotOperator"; // default: Operator
  commands: any[]; // vector<Command> // TODO
  permissions: any[]; // vector<Permission> // TODO

  /**
   * @deprecated
   */
  onLoad(): void;
  onEnable(): void;
  onDisable(): void;
}

declare class JSE {
  static registerPlugin(information: JSE_Plugin_Register): void;

  /**
   * 获取当前插件实例(自身)
   */
  static getPlugin(): Plugin;

  static debug(...args: any[]): void;
}
