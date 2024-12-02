declare interface JSE_Plugin {
  name: string;
  version: string;
  description: string;

  onLoad(): void;
  onEnable(): void;
  onDisable(): void;
}

declare class JSE_EndStone {
  static registerPlugin(information: JSE_Plugin): void;
}
