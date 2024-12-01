declare type PluginInformation = {
  name: string;
  version: string;
  description: string;
};

declare class endstone {
  static registerPlugin(information: PluginInformation): void;
}
