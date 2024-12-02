// "use strict";
/// <reference path="../types/index.d.ts" />

JSE_EndStone.registerPlugin({
  name: "TestLoader",
  version: "1.0.0",
  description: "TestLoader description",
});

JSE_Logger.warn("Test JavaScriptPluginLoader");

const logger = JSE_Logger;
globalThis.onLoad = function () {
  logger.warn("TestLoader onLoad");
};
globalThis.onEnable = function () {
  logger.warn("TestLoader onEnable");
};
globalThis.onDisable = function () {
  logger.warn("TestLoader onDisable");
};
