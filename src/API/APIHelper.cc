#include "APIHelper.h"
#include "Entry.h"

namespace jse
{

    template <typename T>
    bool FindVector(std::vector<T> const &vec, T const &value)
    {
        return std::find(vec.begin(), vec.end(), value) != vec.end();
    }

    bool IsFloat(Local<Value> const &num)
    {
        try
        {
            return fabs(num.asNumber().toDouble() - num.asNumber().toInt64()) >= 1e-15;
        }
        catch (...)
        {
            return false;
        }
    }

    template <typename T>
    bool IsInstanceOf(Local<Value> const &obj)
    {
        return EngineScope::currentEngine()->isInstanceOf<T>(obj);
    }

    string ToString(ValueKind const &kind)
    {
        switch (kind)
        {
        case ValueKind::kNull:
            return "Null";
        case ValueKind::kObject:
            return "Object";
        case ValueKind::kString:
            return "String";
        case ValueKind::kNumber:
            return "Number";
        case ValueKind::kBoolean:
            return "Boolean";
        case ValueKind::kFunction:
            return "Function";
        case ValueKind::kArray:
            return "Array";
        case ValueKind::kByteBuffer:
            return "ByteBuffer";
        case ValueKind::kUnsupported:
        default:
            return "Unknown";
        }
    }
    void ToString(Local<Value> const &value, std::ostringstream &oss)
    {
        switch (value.getKind())
        {
        case ValueKind::kNull:
            oss << "<null>";
            break;
        case ValueKind::kFunction:
            oss << "<function>";
            break;
        case ValueKind::kString:
            oss << value.asString().toString();
            break;
        case ValueKind::kBoolean:
            oss << value.asBoolean().value();
            break;
        case ValueKind::kNumber:
            if (IsFloat(value))
                oss << value.asNumber().toDouble();
            else
                oss << value.asNumber().toInt64();
            break;
        case ValueKind::kByteBuffer:
        {
            Local<ByteBuffer> buffer = value.asByteBuffer();
            oss << (const char *)buffer.getRawBytes(), buffer.byteLength();
            break;
        }
        case ValueKind::kObject:
            ToString(value.asObject(), oss);
            break;
        case ValueKind::kArray:
            ToString(value.asArray(), oss);
            break;
        default:
            oss << "<Unknown>";
        }
    }
    void ToString(Local<Array> const &value, std::ostringstream &oss)
    {
        if (value.size() == 0)
        {
            oss << "[]";
            return;
        }

        static std::vector<Local<Array>> stack;
        if (!FindVector(stack, value))
        {
            stack.push_back(value); // 入栈
            oss << "[";
            for (int i = 0; i < value.size(); ++i)
            {
                if (i > 0)
                    oss << ", ";
                ToString(value.get(i), oss);
            }
            oss << "]";
            stack.pop_back(); // 出栈
        }
        else
        {
            oss << "<Circular Array>"; // 循环引用
        }
    }
    void ToString(Local<Object> const &value, std::ostringstream &oss)
    {
        std::vector<string> keys = value.getKeyNames();
        if (keys.empty())
        {
            oss << "{}";
            return;
        }

        static std::vector<Local<Object>> stack;
        if (!FindVector(stack, value))
        {
            stack.push_back(value); // 入栈
            oss << "{" << keys[0] << ": ";
            ToString(value.get(keys[0]), oss);
            for (int i = 1; i < keys.size(); ++i)
            {
                oss << ", " << keys[i] << ": ";
                ToString(value.get(keys[i]), oss);
            }
            oss << "}";
            stack.pop_back(); // 出栈
        }
        else
        {
            oss << "<Circular Object>"; // 循环引用
        }
    }

    void PrintException(string const &msg)
    {
        auto ptr = GetEntry();
        if (!ptr)
        {
            throw std::runtime_error("GetEntry() failed");
        }

        ptr->getLogger().error("script::Exception: {}", script::Exception(msg).stacktrace());
    }
    void PrintException(script::Exception const &e)
    {
        auto ptr = GetEntry();
        if (!ptr)
        {
            throw std::runtime_error("GetEntry() failed");
        }

        ptr->getLogger().error("script::Exception: {}", e.stacktrace());
    }

}
