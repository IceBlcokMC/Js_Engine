/// <reference path="../types/index.d.ts" />

logger.warn("TestLoader.js is deprecated, use TestLoader.ts instead");

endstone.registerPlugin({
  name: "TestLoader",
  version: "1.0.0",
  description: "TestLoader",
});
function onLoad() {
  logger.info("TestLoader.js loaded");
}

// const MyPlugin = {
//   name: "MyPlugin",
//   version: "1.0.0",
//   description: "MyPlugin",
//   onLoad: () => {},
//   onEnable: () => {},
//   onDisable: () => {},
//   commands: {
//     test: {},
//   },
// };

// endstone.registerPlugin(MyPlugin);
