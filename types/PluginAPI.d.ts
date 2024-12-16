declare class Plugin {
  getDescription(): any; // TODO

  onLoad(): void;

  onEnable(): void;

  onDisable(): void;

  getLogger(): Logger | undefined;

  isEnabled(): boolean;

  getPluginLoader(): any; // TODO

  getServer(): any; // TODO

  getName(): string;

  getCommand(): any; // TODO

  getDataFolder(): string;

  registerEvent(): any; // TODO
}
