/// <reference path="../index.d.ts"/>

declare namespace Enums {
    /** 日志等级 */
    enum LoggerLevel {
        /** 跟踪 */
        Trace,
        /** 调试 */
        Debug,
        /** 信息 */
        Info,
        /** 警告 */
        Warning,
        /** 报错 */
        Error,
        /** 严重错误 */
        Critical,
        /** 关闭 */
        Off
    }
}