// "use strict";
/// <reference path="../types/index.d.ts" />

const logger = JSE_Logger;
JSE_EndStone.register_plugin({
  name: "test_engine",
  description: "测试",
  authors: ["engsr6982"],
  contributors: ["engsr6982"],

  // func
  onLoad: function () {
    logger.warn("onLoad called");
  },

  onEnable: function () {
    logger.warn("onEnable called");

    test_plugin_api();
  },

  onDisable: function () {
    logger.warn("onDisable called");
  },
});

function test_plugin_api() {
  logger.warn("==== Test Plugin API  ====");
  const pl = JSE_EndStone.get_plugin();

  logger.warn("api_version: ", pl.api_version);
}
