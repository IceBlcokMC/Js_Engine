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

  onLoad(): void;
  onEnable(): void;
  onDisable(): void;
}

declare class JSE_EndStone {
  static register_plugin(information: JSE_Plugin_Register): void;

  static get_plugin(): any; // TODO: Define plugin type
}
