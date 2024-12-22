/// <reference path="../dts/index.d.ts"/>

export default function JsonFileConfig<T>(
    path: string,
    defaultConfig: T,
    space?: number | string
): T | Record<string, any>;