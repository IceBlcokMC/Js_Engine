# JS_Engine

JsEngine 基于 ScriptX 和 QuickJs 实现，支持在 EndStone 中运行 JavaScript 插件。

## 安装

> 目前项目处于开发阶段，请手动前往 Actions 查看最新版本。

1. 下载对应平台的 Js_Engine.zip 文件，如: `Js_Engine-windows-x64.zip`

2. 将 Js_Engine.zip 解压，复制 `js_engine.dll` 到 `EndStone\plugins` 目录下

3. 启动你的 endstone 服务器

## 开发

项目没有提供任何开发文档，仅提供了类型定义文件，你可以通过查看类型定义文件来了解 JsEngine 的 API。

您可以参考项目 `test` 目录下的示例代码来了解如何使用 JsEngine。

## 关于项目

### 支持平台

| Platform | Backend | Version    | ECMA Version | Support |
| :------- | :------ | :--------- | :----------- | :------ |
| Windows  | QuickJs | 2021-03-27 | 2020         | y       |
| Linux    | QuickJs | 2024-01-13 | 2023         | x       |

### 从源码编译

#### Windows

```bash
git clone --depth=1 https://github.com/engsr6982/JS_Engine.git
cd JS_Engine

mkdir build/_deps
cd build/_deps

git clone --depth=1 https://github.com/EndstoneMC/endstone.git
mv endstone endstone-src
cd endstone-src

git apply ../../../patch/cxx20.patch

cd ../../..

xmake -y
```

#### Linux(Ubuntu)

暂不支持，具体情况见 build-linux 分支

## 贡献

欢迎提交 Issue 和 Pull Request。
