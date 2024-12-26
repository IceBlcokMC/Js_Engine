/// <reference path="../dts/index.d.ts"/>

/**
 * @param {string} path
 * @param {Object.<string, any> | any[]} defaultConfig
 * @param {number | string} [space=4]
 * @return {Object.<string, any> | any[]}
*/
function JsonFileConfig(path, defaultConfig, space = 4) {
    let content = {};
    try {
        content = JSON.parse(File.readFile(path) ?? defaultConfig);
    } catch {
        if (File.isFile(path)) File.moveFile(path, `${path}.bak`);
    }

    /** @type {ProxyHandler<Object.<string, any> | any[]>} */
    const handler = {
        path: path,
        content: content ?? defaultConfig ?? {},

        get(target, key) {
            this.saveFile();
            return typeof target[key] === "object" ? new Proxy(target[key], handler) : target[key];
        },
        set(target, key, value) {
            target[key] = value;
            this.saveFile();
            return this.get(target, key);
        },

        deleteProperty(target, key) {
            delete target[key];
            this.saveFile();
        },
        saveFile() {
            File.writeFile(
                this.path,
                JSON.stringify(
                    this.content,
                    null,
                    space
                )
            );
        }
    };

    return new Proxy(content ?? defaultConfig ?? {}, handler);
}

// export default JsonFileConfig;
module.exports = JsonFileConfig;