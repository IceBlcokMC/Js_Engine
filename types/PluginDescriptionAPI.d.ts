declare class PluginDescriptionAPI {
  getName(): string;

  getVersion(): string;

  getFullName(): string;

  getAPIVersion(): string;

  getDescription(): string;

  getLoad(): PluginLoadOrder;

  getAuthors(): string[];

  getContributors(): string[];

  getWebsite(): string;

  getPrefix(): string;

  getProvides(): string[];

  getDepend(): string[];

  getSoftDepend(): string[];

  getLoadBefore(): string[];

  getDefaultPermission(): PermissionDefault;

  getCommands(): any; // TODO:

  getPermissions(): any; // TODO:
}
