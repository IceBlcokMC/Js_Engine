/// <reference path="../dts/index.d.ts"/>

export function JsonFileConfig<T>(
    /** 文件路径 */
    path: string,
    /** 默认内容 */
    defaultConfig: T,
    /** 缩进 */
    space?: number | string
): T | Record<string, any>;