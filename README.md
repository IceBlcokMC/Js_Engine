# JS_Engine

| 中文 | [English](./README-EN.md) |

JsEngine 基于 ScriptX 和 NodeJs 实现，支持在 EndStone 中运行 JavaScript 插件。

## 安装

> 目前项目处于开发阶段，请手动前往 Actions 查看最新版本。

1. 下载对应平台的 Js_Engine-full.zip 文件，如: `Js_Engine-windows-full-x64.zip`

> full 为完整包，包含 LibNodeJs 和 JsEngine 的依赖库

2. 将 Js_Engine-full.zip 解压，将压缩包内 libnode.xx 和 plugins 目录复制到 bedrock_server 的根目录下

> 示例结构

```tree
.
├── bedrock_server
│   ├── bedrock_server.exe
│   ├── libnode.xx
│   └── plugins
│       ├── js_engine
│       │   ├── node_modules
│       │   ├── dts
│       │   └── ...
│       └── js_engine.dll
└── ...
```

3. 启动你的 endstone 服务器

## 开发

目前项目没有任何开发文档，您可以阅读 `lib/dts` 目录下的类型定义文件，了解 JsEngine 的 API。

## 关于项目

### 支持平台

| Platform | Backend | Version | Support | CommonJs | ESM | package manager |
| :------- | :------ | :------ | :------ | :------- | :-- | :-------------- |
| Windows  | NodeJs  | v23.5.0 | y       | y        | y   | npm             |
| Linux    | NodeJs  | v23.5.0 | y       | y        | y   | npm             |

### 从源码编译

在编译之前，确保您已经安装了以下工具链：

- xmake
- MSVC 2019 或更高版本 (仅限 Windows)
- LLVM 15 (附带 Clang、libc++) (仅限 Linux)

```bash
git clone --depth=1 https://github.com/engsr6982/JS_Engine.git
cd JS_Engine
xmake -y
```

## 贡献

欢迎提交 Issue 和 Pull Request。
