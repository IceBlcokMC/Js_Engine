// "use strict";
/// <reference path="../types/index.d.ts" />

const logger = JSE_Logger;
JSE_EndStone.register_plugin({
  name: "TestLoader",
  version: "1.0.0",
  description: "TestLoader description",

  onLoad: () => {
    logger.warn("TestLoader loaded");
  },
  onEnable: () => {
    logger.warn("TestLoader enabled");
  },
  onDisable: () => {
    logger.warn("TestLoader disabled");
  },
});
