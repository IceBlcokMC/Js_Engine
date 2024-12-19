declare namespace Enums {
  enum LoggerLevel {
    "Trace",
    "Debug",
    "Info",
    "Warning",
    "Error",
    "Critical",
    "Off"
  }
}

declare class Logger {
  log(level: Enums.LoggerLevel, ...message: any[]): boolean;
  info(...message: any[]): boolean;
  warning(...message: any[]): boolean;
  error(...message: any[]): boolean;
  debug(...message: any[]): boolean;
  trace(...message: any[]): boolean;
  critical(...message: any[]): boolean;

  setLevel(level: Enums.LoggerLevel): void;
  isEnabledFor(level: Enums.LoggerLevel): boolean;
  getName(): string;
}
