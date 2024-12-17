"use strict";

JSE.registerPlugin({
  name: "test_js_plugin",
  description: "测试",
  authors: ["engsr6982"],
  contributors: ["engsr6982"],

  // func
  onLoad: function () {
    JSE.debug("onLoad called");
  },

  onEnable: function () {
    JSE.debug("onEnable called");
    test_plugin();
    test_logger();
    checkTypeOf();
  },

  onDisable: function () {
    JSE.debug("onDisable called");
  },
});

const plugin = JSE.getPlugin();
function test_plugin() {
  JSE.debug("==== Test Plugin ====");
  JSE.debug(`isEnabled: ${plugin.isEnabled()}`);
  JSE.debug(`getName: ${plugin.getName()}`);
  JSE.debug(`getDataFolder: ${plugin.getDataFolder()}`);
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

function checkTypeOf() {
  JSE.debug("==== Check Type Of ====");
  JSE.debug(`Logger: `, logger);
  JSE.debug(`Plugin: `, plugin);
}
