#pragma once
#include "utils/Defines.h"
#include "utils/Using.h"

namespace jse {
class FileAPI : public ScriptClass {
public:
    explicit FileAPI() : ScriptClass(ScriptClass::ConstructFromCpp<FileAPI>{}) {}

    static Local<Object> newFileAPI() { return (new FileAPI())->getScriptObject(); }

public:
    static METHODS(readFile);

    static METHODS(writeFile);

    static METHODS(createDirectory);

    static METHODS(copyFile);

    static METHODS(moveFile);

    static METHODS(del);

    static METHODS(exists);

    static METHODS(isDirectory);

    static METHODS(isFile);

    static METHODS(getFileSize);

    static METHODS(listDirectory);

    static ClassDefine<void> builder;
};
} // namespace jse