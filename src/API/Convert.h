#pragma once


#include "Engine/Using.h"
#include "magic_enum/magic_enum.hpp"
#include <type_traits>
#include <unordered_map>
namespace jse {


namespace ConvertImpl {

// 基础模板
template <typename T, typename Enable = void>
struct ToScriptType {
    static_assert(sizeof(T) == 0, "Unsupported type conversion");
};

// 特化类型
template <>
struct ToScriptType<std::string> {
    using Type = String;
};

template <>
struct ToScriptType<const char*> {
    using Type = String;
};

template <>
struct ToScriptType<int> {
    using Type = Number;
};

template <>
struct ToScriptType<double> {
    using Type = Number;
};

template <>
struct ToScriptType<bool> {
    using Type = Boolean;
};

// 数组转换
template <typename T>
struct ToScriptType<std::vector<T>> {
    using Type = Array;
};

// map转换 (key必须是string)
template <typename V>
struct ToScriptType<std::unordered_map<std::string, V>> {
    using Type = Object;
};

// enum
template <typename T>
struct ToScriptType<T, std::enable_if_t<std::is_enum_v<T>>> {
    using Type = String;
};

// 实现
template <typename T>
Local<Value> ConvertToScriptImpl(const T& value) {
    using ScriptType = typename ToScriptType<T>::Type;

    if constexpr (std::is_enum_v<T>) {
        return String::newString(magic_enum::enum_name(value)); // enum -> string
    } else if constexpr (std::is_same_v<ScriptType, String>) {
        return String::newString(value); // string -> string
    } else if constexpr (std::is_same_v<ScriptType, Number>) {
        return Number::newNumber(value); // int、double、float -> number
    } else if constexpr (std::is_same_v<ScriptType, Boolean>) {
        return Boolean::newBoolean(value); // bool -> boolean
    } else if constexpr (std::is_same_v<ScriptType, Array>) {
        auto arr = Array::newArray(); // vector<T> -> array
        for (const auto& item : value) {
            arr.add(ConvertToScriptImpl(item));
        }
        return arr;
    } else if constexpr (std::is_same_v<ScriptType, Object>) {
        auto obj = Object::newObject(); // unordered_map<string, V> -> object
        for (const auto& [key, val] : value) {
            obj.set(key, ConvertToScriptImpl(val));
        }
        return obj;
    }
}

} // namespace ConvertImpl

template <typename T>
Local<Value> ConvertToScript(const T& value) {
    return ConvertImpl::ConvertToScriptImpl(value);
}

} // namespace jse