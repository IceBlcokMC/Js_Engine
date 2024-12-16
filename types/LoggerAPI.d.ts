// endstone logger.h

/**
 * 0: Trace
 * 1: Debug
 * 2: Info
 * 3: Warning
 * 4: Error
 * 5: Critical
 * 6: Off
 */
type LoggerLevel = 0 | 1 | 2 | 3 | 4 | 5 | 6;

declare class JSE_Logger {
  static log(level: LoggerLevel, ...message: any[]): boolean;
  static info(...message: any[]): boolean;
  static warning(...message: any[]): boolean;
  static error(...message: any[]): boolean;
  static debug(...message: any[]): boolean;
  static trace(...message: any[]): boolean;
  static critical(...message: any[]): boolean;

  static setLevel(level: LoggerLevel): void;
  static isEnabledFor(level: LoggerLevel): boolean;
  static getName(): string;
}
