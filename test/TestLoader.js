/// <reference path="../types/index.d.ts" />

logger.warn("Test JavaScriptPluginLoader");

endstone.registerPlugin({
  name: "TestLoader",
  version: "1.0.0",
  description: "TestLoader description",
});

function onLoad() {
  logger.warn("TestLoader.js loaded");
}

function onEnable() {
  logger.warn("TestLoader.js enabled");
}

function onDisable() {
  logger.warn("TestLoader.js disabled");
}

const aaa = {
  
}
