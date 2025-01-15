#include "api/jse/FileAPI.h"
#include "api/APIHelper.h"
#include "utils/FileUtils.h"
#include <filesystem>

namespace jse {

ClassDefine<void> FileAPI::builder = defineClass("FileAPI")
                                         .function("readFile", &FileAPI::readFile)
                                         .function("writeFile", &FileAPI::writeFile)
                                         .function("createDirectory", &FileAPI::createDirectory)
                                         .function("copyFile", &FileAPI::copyFile)
                                         .function("moveFile", &FileAPI::moveFile)
                                         .function("delete", &FileAPI::del)
                                         .function("exists", &FileAPI::exists)
                                         .function("isDirectory", &FileAPI::isDirectory)
                                         .function("isFile", &FileAPI::isFile)
                                         .function("getFileSize", &FileAPI::getFileSize)
                                         .function("listDirectory", &FileAPI::listDirectory)
                                         .build();


Local<Value> FileAPI::readFile(Arguments const& args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kString);
    if (args.size() >= 2) {
        CheckArgType(args[1], ValueKind::kBoolean);
    }

    auto content = ll::file_utils::readFile(
        args[0].asString().toU8string(),
        args.size() >= 2 ? args[1].asBoolean().value() : false
    );
    return content.has_value() ? String::newString(content.value()) : Local<Value>();
}

Local<Value> FileAPI::writeFile(Arguments const& args) try {
    CheckArgsCount(args, 2);
    CheckArgType(args[0], ValueKind::kString);
    CheckArgType(args[1], ValueKind::kString);
    if (args.size() >= 3) {
        CheckArgType(args[2], ValueKind::kBoolean);
    }

    return Boolean::newBoolean(ll::file_utils::writeFile(
        args[0].asString().toU8string(),
        args[1].asString().toString(),
        args.size() >= 3 ? args[2].asBoolean().value() : false
    ));
}
Catch;

Local<Value> FileAPI::createDirectory(Arguments const& args) try {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kString);

    return Boolean::newBoolean(std::filesystem::create_directories(args[0].asString().toU8string()));
} catch (std::filesystem::filesystem_error const& error) {
    throw script::Exception(error.what());
}
Catch;

Local<Value> FileAPI::copyFile(Arguments const& args) try {
    CheckArgsCount(args, 2);
    CheckArgType(args[0], ValueKind::kString);
    CheckArgType(args[1], ValueKind::kString);

    std::filesystem::copy(args[0].asString().toU8string(), args[1].asString().toU8string());
    return Boolean::newBoolean(true);
} catch (std::filesystem::filesystem_error const& error) {
    throw script::Exception(error.what());
}
Catch;

Local<Value> FileAPI::moveFile(Arguments const& args) try {
    CheckArgsCount(args, 2);
    CheckArgType(args[0], ValueKind::kString);
    CheckArgType(args[1], ValueKind::kString);

    std::filesystem::rename(args[0].asString().toU8string(), args[1].asString().toU8string());
    return Boolean::newBoolean(true);
} catch (std::filesystem::filesystem_error const& error) {
    throw script::Exception(error.what());
}
Catch;

Local<Value> FileAPI::del(Arguments const& args) try {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kString);

    return Boolean::newBoolean(std::filesystem::remove(args[0].asString().toU8string()));
} catch (std::filesystem::filesystem_error const& error) {
    throw script::Exception(error.what());
}
Catch;

Local<Value> FileAPI::exists(Arguments const& args) try {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kString);

    return Boolean::newBoolean(std::filesystem::exists(args[0].asString().toU8string()));
}
Catch;

Local<Value> FileAPI::getFileSize(Arguments const& args) try {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kString);

    auto path = args[0].asString().toU8string();

    if (!std::filesystem::exists(path)) throw script::Exception("File does not exist");
    if (!std::filesystem::is_regular_file(path)) throw script::Exception("Path is not a file");

    return Number::newNumber((int64_t)std::filesystem::file_size(path));
}
Catch;

Local<Value> FileAPI::isDirectory(Arguments const& args) try {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kString);

    return Boolean::newBoolean(std::filesystem::is_directory(args[0].asString().toU8string()));
}
Catch;

Local<Value> FileAPI::isFile(Arguments const& args) try {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kString);

    return Boolean::newBoolean(std::filesystem::is_regular_file(args[0].asString().toU8string()));
}
Catch;

Local<Value> FileAPI::listDirectory(Arguments const& args) try {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kString);

    auto result = Array::newArray();
    for (auto& name : ll::file_utils::getFileList(args[0].asString().toU8string())) {
        result.add(String::newString(name));
    }
    return result;
}
Catch;
} // namespace jse