import process from "process";
import path from "path";
import fs from "fs";

/**
 * @param {string} class_
 * @param {string[]} methods
 * @param {string} parent_class
 * @returns {string}
 */
function genDts(class_, methods, parent_class = null) {
    let dts = `declare class ${class_}`;

    if (parent_class) {
        dts += ` extends ${parent_class} {\n`;
    } else {
        dts += ` {\n`;
    }

    /**
     * @param {string} fn
     * @param {string[]} params
     * @param {string} return_
     */
    const func = (fn, params, return_) => {
        return `\t${fn}(${params.join(", ")}): ${return_};\n`;
    };

    methods.forEach((fn) => {
        if (fn == "toString") {
            dts += func(fn, [], `"<${class_}>" | string`);
            return;
        }
        dts += func(fn, [], "any");
    });

    dts += `}\n`;
    return dts;
}

/**
 *
 * @param {string} contents
 */
function getFunctions(contents) {
    const classRegx = /class\s+(\w+)\s*:\s*public\s+(\w+)\s*{/; // 带继承
    const classRegx2 = /class\s+(\w+)\s*{/; // 不带继承
    const funcRegx = /(static\s+)?METHODS\((\w+)\);/g;

    let class_ = contents.match(classRegx);
    if (!class_) {
        class_ = contents.match(classRegx2);
        if (!class_) {
            throw new Error("No class found");
        }
    }

    class_.shift();
    for (let i = 0; i < class_.length; i++) {
        const c = class_[i];
        if (c == "ScriptClass") {
            class_.splice(i, 1);
            continue;
        }

        class_[i] = c.replace(/API/g, "");
    }

    const methods = [];
    let tmp;
    while ((tmp = funcRegx.exec(contents))) {
        if (tmp[1] && tmp[1] == "static ") {
            methods.push(`${tmp[1]}${tmp[2]}`); // static func
        } else {
            methods.push(tmp[2]); // instance func
        }
    }

    return {
        class_: class_,
        methods: methods,
    };
}

function readFile(file) {
    return fs.readFileSync(file, "utf8");
}

function writeFile(file, contents) {
    fs.writeFileSync(file, contents);
}

function getAllHeaderFiles(dir) {
    const files = fs
        .readdirSync(dir)
        .filter((file) => path.extname(file) === ".h");
    return files.map((file) => path.join(dir, file));
}

function findHeader(dir) {
    let files = [...getAllHeaderFiles(dir)];

    // 递归搜索子文件夹下的文件
    fs.readdirSync(dir).forEach((file) => {
        const filePath = path.join(dir, file);
        if (fs.statSync(filePath).isDirectory()) {
            files = [...files, ...getAllHeaderFiles(filePath)];
        }
    });

    files.filter((f) => f.endsWith(".h"));

    return files;
}

function main() {
    const dir = path.join("./src/API");
    const exclude = ["APIHelper.h", "EnumAPI.h"];

    let files = findHeader(dir);

    exclude.forEach((file) => {
        files = files.filter((f) => !f.endsWith(file));
    });

    if (!fs.existsSync("out")) {
        fs.mkdirSync("out");
    }

    for (const file of files) {
        const contents = readFile(file);
        const { class_, methods } = getFunctions(contents);
        const dts = genDts(class_[0], methods, class_[1]);
        writeFile(path.join("out", `${class_[0]}.d.ts`), dts);
    }
}

main();
