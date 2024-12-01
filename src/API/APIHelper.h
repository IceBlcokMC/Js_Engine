#pragma once
#include "Engine/Using.h"
#include "Entry.h"
#include <iostream>

namespace jse
{
    template <typename T>
    bool FindVector(std::vector<T> const &vec, T const &value);

    bool IsFloat(Local<Value> const &num);

    string ToString(ValueKind const &kind);
    string ToString(Local<Value> const &value);
    void ToString(Local<Value> const &value, std::ostringstream &oss);
    void ToString(Local<Array> const &value, std::ostringstream &oss);
    void ToString(Local<Object> const &value, std::ostringstream &oss);

    template <typename T>
    bool IsInstanceOf(Local<Value> const &value);

    void PrintException(string const &msg);
    void PrintException(script::Exception const &e);

// 工具宏
#define PrintScriptError(...)    \
    PrintException(__VA_ARGS__); \
    std::cout << "\x1b[91mIn function: " << __FUNCTION__ << "\x1b[0m" << std::endl;

// 参数异常
#define PrintWrongArgType() PrintScriptError("Wrong argument type")
#define PrintArgsTooFew() PrintScriptError("Too few arguments")
#define PrintWrongArgsCount() PrintScriptError("Wrong arguments count")

// 检查参数数量
#define CheckArgsCount(args, count) \
    if (args.size() < count)        \
    {                               \
        PrintArgsTooFew();          \
        return Local<Value>();      \
    }

// 检查参数类型
#define CheckArgType(arg, type) \
    if (arg.getKind() != type)  \
    {                           \
        PrintWrongArgType();    \
        return Local<Value>();  \
    }

// 异常捕获
#define Catch                                                      \
    catch (script::Exception const &e)                             \
    {                                                              \
        if (GetEntry())                                            \
            GetEntry()->getLogger().error("Fail in {}", __func__); \
        PrintException(e);                                         \
        return Local<Value>();                                     \
    }                                                              \
    catch (...)                                                    \
    {                                                              \
        if (GetEntry())                                            \
            GetEntry()->getLogger().error("Fail in {}", __func__); \
        PrintScriptError("");                                        \
        return Local<Value>();                                     \
    }

#define CatchNotReturn                                             \
    catch (script::Exception const &e)                             \
    {                                                              \
        if (GetEntry())                                            \
            GetEntry()->getLogger().error("Fail in {}", __func__); \
        PrintException(e);                                         \
    }                                                              \
    catch (...)                                                    \
    {                                                              \
        if (GetEntry())                                            \
            GetEntry()->getLogger().error("Fail in {}", __func__); \
        PrintScriptError("");                                        \
    }

}