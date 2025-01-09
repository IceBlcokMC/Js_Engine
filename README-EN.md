# JS_Engine

| [中文](./README.md) | English |

JsEngine is implemented based on ScriptX and NodeJs, supporting JavaScript plugins running in EndStone.

## 📌 Installation

> 🚧 The project is currently under development. Please check the latest version manually in Actions.

1. Download the Js_Engine-full.zip file for your platform, e.g., `Js_Engine-windows-full-x64.zip`

> 'full' package includes LibNodeJs and JsEngine dependencies

2. Extract Js_Engine-full.zip, copy the libnode.xx and plugins directories from the package to the root directory of bedrock_server

> Example structure:

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

3. Start your endstone server

## 📗 Development

Currently, there is no development documentation available. You can read the type definition files in the `lib/dts` directory, or use the template items we provide [Js_Engine_Plugin_Template](https://github.com/IceBlcokMC/js_engine_plugin_template)。

## 💻 Supported Platforms

| Platform | Backend | Version | CommonJs | ESM | package manager |
| :------- | :------ | :------ | :------- | :-- | :-------------- |
| Windows  | NodeJs  | v22.12.0 | y        | y   | npm             |
| Linux    | NodeJs  | v22.12.0 | y        | y   | npm             |

## 🔨 Building from Source

Before building, make sure you have installed the following toolchains:

- Xmake
- MSVC++ 2019 or higher (Windows only)
- LLVM 15 (with Clang, libc++) (Linux only)

```bash
git clone --depth=1 https://github.com/engsr6982/JS_Engine.git
cd JS_Engine
xmake -y
```

## 🎬 Contributing

Issues and Pull Requests are welcome.

## 📍 License

This project is licensed under the GPL-3.0 License - see the [LICENSE](LICENSE) file for details.
