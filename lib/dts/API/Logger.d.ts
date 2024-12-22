/// <reference path="../index.d.ts"/>

/** 日志输出 */
declare class Logger {
    private constructor();

    toString(): "<Logger>";

    /** 输出日志 */
    log(level: Enums.LoggerLevel, ...message: any[]): boolean;
    /** 输出信息日志 */
    info(...message: any[]): boolean;
    /** 输出警告日志 */
    warning(...message: any[]): boolean;
    /** 输出错误日志 */
    error(...message: any[]): boolean;
    /** 输出调试日志 */
    debug(...message: any[]): boolean;
    /** 输出跟踪日志 */
    trace(...message: any[]): boolean;
    /** 输出致命错误日志 */
    critical(...message: any[]): boolean;
  
    /** 设置日志输出等级 */
    setLevel(level: Enums.LoggerLevel): void;
    /** 是否可输出指定日志等级的日志 */
    isEnabledFor(level: Enums.LoggerLevel): boolean;
    /** 获取日志标题 */
    getName(): string;
  }