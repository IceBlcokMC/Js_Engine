// "use strict";
/// <reference path="../types/index.d.ts" />

JSE_EndStone.register_plugin({
  name: "test_engine",
  description: "测试",
  authors: ["engsr6982"],
  contributors: ["engsr6982"],

  // func
  onLoad: function () {
    JSE_Logger.warning("onLoad called");
  },

  onEnable: function () {
    JSE_Logger.warning("onEnable called");
    test_logger();
    test_plugin_api();
  },

  onDisable: function () {
    JSE_Logger.warning("onDisable called");
  },
});

function test_logger() {
  JSE_Logger.setLevel(6);
  JSE_Logger.debug("==== Test Logger  ====");
  JSE_Logger.info("==== Test Logger  ====");
  JSE_Logger.warning("==== Test Logger  ====");
  JSE_Logger.error("==== Test Logger  ====");
  JSE_Logger.trace("==== Test Logger  ====");
  JSE_Logger.critical("==== Test Logger  ====");
  JSE_Logger.info(
    `enable: ${JSE_Logger.isEnabledFor(6)}, name: ${JSE_Logger.getName()}`
  );
}

function test_plugin_api() {
  JSE_Logger.warning("==== Test Plugin API  ====");
  const pl = JSE_EndStone.get_plugin();

  JSE_Logger.warning("api_version: ", pl.api_version);
}
