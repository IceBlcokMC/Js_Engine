/**
 * 0: Trace
 * 1: Debug
 * 2: Info
 * 3: Warning
 * 4: Error
 * 5: Critical
 * 6: Off
 * https://endstone.readthedocs.io/en/latest/reference/cpp/logger_8h_source/
 */
declare type LoggerLevel = 0 | 1 | 2 | 3 | 4 | 5 | 6;

declare class Logger {
  log(level: LoggerLevel, ...message: any[]): boolean;
  info(...message: any[]): boolean;
  warning(...message: any[]): boolean;
  error(...message: any[]): boolean;
  debug(...message: any[]): boolean;
  trace(...message: any[]): boolean;
  critical(...message: any[]): boolean;

  setLevel(level: LoggerLevel): void;
  isEnabledFor(level: LoggerLevel): boolean;
  getName(): string;
}
