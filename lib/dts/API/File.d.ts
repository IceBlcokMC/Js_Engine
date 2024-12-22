/// <reference path="../index.d.ts"/>

declare class File {
    private constructor();

    /** 读取文件 */
    static readFile(
        /** 文件路径 */
        path: string,
        /** 以二进制读取 */
        isBinary?: boolean
    ): string | undefined;

    /** 写入文件 */
    static writeFile(
        /** 文件路径 */
        path: string,
        /** 文件内容 */
        content: string,
        /** 以二进制写入 */
        isBinary?: boolean
    ): boolean;

    /** 创建文件夹 */
    static createDirectory(
        /** 文件夹路径 */
        path: string
    ): boolean;

    /** 复制文件 */
    static copyFile(
        /** 源文件路径 */
        source: string,
        /** 目标文件路径 */
        target: string
    ): boolean;

    /** 移动文件 */
    static moveFile(
        /** 源文件路径 */
        source: string,
        /** 目标文件路径 */
        target: string
    ): boolean;

    /** 删除文件/文件夹 */
    static delete(
        /** 文件/文件夹路径 */
        path: string
    ): boolean;

    /** 文件/文件夹是否存在 */
    static exists(
        /** 文件/文件夹路径 */
        path: string
    ): boolean;

    /** 获取文件大小 */
    static getFileSize(
        /** 文件路径 */
        path: string
    ): number;

    /** 路径是否为文件夹 */
    static isDirectory(
        /** 文件/文件夹路径 */
        path: string
    ): boolean;

    /** 路径是否为文件 */
    static isFile(
        /** 文件/文件夹路径 */
        path: string
    ): boolean;

    /** 获取文件/文件夹列表 */
    static listDirectory(
        /** 文件夹路径 */
        path: string
    ): string[];
}