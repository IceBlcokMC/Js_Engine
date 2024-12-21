# JS_Engine

JsEngine 基于 ScriptX 和 QuickJs 实现，支持在 EndStone 中运行 JavaScript 插件。

## 安装

> 目前项目处于开发阶段，请手动前往 Actions 查看最新版本。

1. 下载对应平台的 Js_Engine.zip 文件，如: `Js_Engine-windows-x64.zip`

2. 将 Js_Engine.zip 解压，复制 `js_engine.dll` 到 `EndStone\plugins` 目录下

3. 启动你的 endstone 服务器

## 开发

目前项目没有任何开发文档，您可以阅读 `types` 目录下的类型定义文件，了解 JsEngine 的 API。

## 关于项目

### 支持平台

| Platform | Backend | Version    | ECMA Version | Support |
| :------- | :------ | :--------- | :----------- | :------ |
| Windows  | QuickJs | 2021-03-27 | 2020         | y       |
| Linux    | QuickJs | 2024-01-13 | 2023         | y       |

### 从源码编译

在编译之前，确保您已经安装了以下工具链：

- Xmake
- MSVC++ 2019 或更高版本 (仅限 Windows)
- LLVM 15 (附带 Clang、libc++) (仅限 Linux)

```bash
git clone --depth=1 https://github.com/engsr6982/JS_Engine.git
cd JS_Engine
xmake -y
```

## 贡献

欢迎提交 Issue 和 Pull Request。
