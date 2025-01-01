// / <reference path="./js_engine/dts/index.d.ts"/>

console.log("[Main] Current working directory:", process.cwd());
console.log("[Main] Module paths:", module.paths);
console.log("[Main] __dirname:", __dirname);
console.log("[Main] __filename:", __filename);

try {
    require("../js_engine/lib/shortcutApi/JsonFileConfig.js");
    require("./b.js")(); // TODO: Fix this require root path error
} catch (e) {
    console.error(e);
}

JSE.registerPlugin({
    name: "test_js_plugin",
    version: "114514",
    description: "测试",
    load: Enums.PluginLoadOrder.PostWorld,
    authors: ["engsr6982"],
    contributors: ["engsr6982", "zimuya4153"],
    website: "https://github.com/engsr6982",
    prefix: "JSPluginTest",
    permissions: {
        "test.js_plugin.hello": {
            description: "test permission",
            default: Enums.PermissionDefault.True,
        },
        "test.a1": {
            description: "test permission",
            default: Enums.PermissionDefault.True,
        },
    },
    commands: {
        hello: {
            description: "hello test command",
            usages: ["/hello"],
            permissions: ["test.js_plugin.hello", "test.a1"],
        },
    },

    onLoad: () => {
        JSE.debug("onLoad called");
    },

    onEnable: () => {
        JSE.debug("onEnable called");
        const plugin = JSE.getPlugin(),
            logger = plugin.getLogger(),
            description = plugin.getDescription();

        (() => {
            JSE.debug("==== Test Plugin ====");
            JSE.debug(`isEnabled: `, plugin.isEnabled());
            JSE.debug(`getName: `, plugin.getName());
            JSE.debug(`getDataFolder: `, plugin.getDataFolder());
        })();

        (() => {
            JSE.debug("==== Test Logger ====");
            logger.setLevel(0);
            logger.log(Enums.LoggerLevel.Info, "logger log");
            logger.debug("logger debug");
            logger.info("logger info");
            logger.warning("logger warning");
            logger.error("logger error");
            logger.trace("logger trace");
            logger.critical("logger critical");
            logger.info(
                `enable: ${logger.isEnabledFor(5)}, name: ${logger.getName()}`
            );
            logger.info(
                new Array(3)
                    .fill()
                    .map((_, i) => `Test Line: ${i}`)
                    .join("\n")
            );
        })();

        (() => {
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
        })();

        (() => {
            JSE.debug("==== Custom Class toString ====");
            JSE.debug(`Logger: `, logger);
            JSE.debug(`Plugin: `, plugin);
            JSE.debug(`PluginDescription: `, description);
            JSE.debug(`Test Class1: `, new (class Test1 { })());
            JSE.debug(
                `Test Class2: `,
                new (class Test2 {
                    toString() {
                        return "<Test Class2>";
                    }
                })()
            );
        })();
    },

    onDisable: () => {
        JSE.debug("onDisable called");
    },

    onCommand: (sender) => {
        JSE.debug("onCommand called");
        JSE.debug("sender: ", sender);
        JSE.debug("sender.sendMessage: ", sender.sendMessage);
        sender?.sendMessage("Hello: ", sender?.getName());
    },
});
