/*

dts.js - 根据特征使用正则表达式生成dts文件

使用方法：
    node dts.js <dir_or_file>

*/

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
        return `\t${fn}(${params.join(", ")}): ${return_};\n\n`;
    };

    methods.forEach((fn) => {
        if (fn == "toString") {
            dts += func(fn, [], `"<${class_}>" | string`);
            return;
        }
        dts += func(fn, [], "any");
    });

    if (dts.endsWith("\n\n")) {
        dts = dts.slice(0, -1); // 去掉最后的换行
    }

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

/**
 * @param {string} file
 * @param {string} output_dir
 */
function processFile(file, output_dir) {
    const filename = path.basename(file);
    if (!filename.endsWith(".h")) {
        return;
    }

    const exclude = ["APIHelper.h", "EnumAPI.h"];
    if (exclude.includes(filename)) {
        return;
    }

    const contents = readFile(file);
    const { class_, methods } = getFunctions(contents);
    const dts = genDts(class_[0], methods, class_[1]);

    // 计算相对于输入目录的相对路径
    const relativePath = path.relative(process.argv[2], path.dirname(file));
    const outputSubDir = path.join(output_dir, relativePath);
    if (!fs.existsSync(outputSubDir)) {
        fs.mkdirSync(outputSubDir, { recursive: true });
    }
    writeFile(path.join(outputSubDir, `${class_[0]}.d.ts`), dts);
    console.log(`${file} -> ${outputSubDir}/${class_[0]}.d.ts`);
}

/**
 * @param {string} dir
 * @param {string} output_dir
 */
function processDir(dir, output_dir) {
    const files = fs.readdirSync(dir);
    files.forEach((file) => {
        const file_path = path.join(dir, file);
        if (fs.statSync(file_path).isDirectory()) {
            processDir(file_path, output_dir);
            return;
        }
        processFile(file_path, output_dir);
    });
}

function main() {
    const file_or_dir = process.argv[2];
    const project_dir = process.cwd();
    const output_dir = path.join(project_dir, "tmp");
    if (!fs.existsSync(output_dir)) {
        fs.mkdirSync(output_dir);
    }

    if (!fs.statSync(file_or_dir).isDirectory()) {
        processFile(file_or_dir, output_dir);
        return;
    }

    processDir(file_or_dir, output_dir);
}

main();
