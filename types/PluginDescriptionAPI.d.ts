/**
 * Represents the order in which a plugin should be initialized and enabled.
 * plugin_load_order.h
 */
type PluginLoadOrder =
  /**
   * Indicates that the plugin will be loaded at startup
   */
  | "Startup"
  /**
   * Indicates that the plugin will be loaded after the first/default world
   * was created
   */
  | "PostWorld";

/** permission_default.h */
type PermissionDefault = "True" | "False" | "Operator" | "NotOperator";

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
