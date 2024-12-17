"use strict";

JSE.registerPlugin({
  name: "test_js_plugin",
  version: "114514",
  description: "测试",
  load: "PostWorld",
  authors: ["engsr6982"],
  contributors: ["engsr6982"],
  website: "https://github.com/engsr6982",
  prefix: "JsPlugin",

  // func
  onLoad: function () {
    JSE.debug("onLoad called");
  },

  onEnable: function () {
    JSE.debug("onEnable called");
    test_plugin();
    test_logger();
    testPluginDescription();
    checkTypeOf();
  },

  onDisable: function () {
    JSE.debug("onDisable called");
  },
});

const plugin = JSE.getPlugin();
function test_plugin() {
  JSE.debug("==== Test Plugin ====");
  JSE.debug(`isEnabled: `, plugin.isEnabled());
  JSE.debug(`getName: `, plugin.getName());
  JSE.debug(`getDataFolder: `, plugin.getDataFolder());
}

const logger = plugin.getLogger();
function test_logger() {
  JSE.debug("==== Test Logger ====");
  logger.setLevel(0);
  logger.debug("logger debug");
  logger.info("logger info");
  logger.warning("logger warning");
  logger.error("logger error");
  logger.trace("logger trace");
  logger.critical("logger critical");
  logger.info(`enable: ${logger.isEnabledFor(5)}, name: ${logger.getName()}`);
}

const description = plugin.getDescription();
function testPluginDescription() {
  JSE.debug("==== Test PluginDescription ====");
  JSE.debug("getName: ", description.getName());
  JSE.debug("getVersion: ", description.getVersion());
  JSE.debug("getFullName: ", description.getFullName());
  JSE.debug("getAPIVersion: ", description.getAPIVersion());
  JSE.debug("getDescription: ", description.getDescription());
  JSE.debug("getLoad: ", description.getLoad());
  JSE.debug("getAuthors: ", description.getAuthors());
  JSE.debug("getContributors: ", description.getContributors());
  JSE.debug("getWebsite: ", description.getWebsite());
  JSE.debug("getPrefix: ", description.getPrefix());
  JSE.debug("getProvides: ", description.getProvides());
  JSE.debug("getDepend: ", description.getDepend());
  JSE.debug("getSoftDepend: ", description.getSoftDepend());
  JSE.debug("getLoadBefore: ", description.getLoadBefore());
  JSE.debug("getDefaultPermission: ", description.getDefaultPermission());
}

function checkTypeOf() {
  JSE.debug("==== Custom Class toString ====");
  JSE.debug(`Logger: `, logger);
  JSE.debug(`Plugin: `, plugin);
  JSE.debug(`PluginDescription: `, description);
}
