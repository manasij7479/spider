#ifndef SPIDER_TYPE_OPS_HPP
#define SPIDER_TYPE_OPS_HPP
#include "Runtime/Type.hpp"
#include "Runtime/GraphValue.hpp"
#include "Runtime/WindowValue.hpp"
#include <algorithm>
namespace spider
{
    inline void assert_type(Value* x, VType t)
    {
        if (x->type != t)
            throw std::runtime_error("Type Mismatch: Expected: '"+Value::TypeToNameMap()[t]+"'. Got: '"+Value::TypeToNameMap()[x->type]+"' \n");
    }
    template <typename T>
    void assert_size(std::vector<T> args, int size, std::string reason = "<>")
    {
        if (args.size() != size)
            throw std::runtime_error("Size Mismatch."+reason+"\n");
    }
    template <typename T>
    void assert_size(std::vector<T> args, std::function<bool(int)> predicate, std::string reason = "<>")
    {
        if (predicate(args.size()) == false)
            throw std::runtime_error("Size Mismatch."+reason+"\n");
    }

    inline std::function<bool(int)> greater(int i)
    {
        return [i](int x){return x > i;};
    }
    inline std::function<bool(int)> lesser(int i)
    {
        return [i](int x){return x < i;};
    }
    inline std::function<bool(int)> greater_eq(int i)
    {
        return [i](int x){return x >= i;};
    }
    inline std::function<bool(int)> lesser_eq(int i)
    {
        return [i](int x){return x <= i;};
    }
    
    
    inline GraphValue* getg(Value* v)
    {
        return static_cast<GraphValue*>(v);
    }
    inline StringValue* gets(Value* v)
    {
        return static_cast<StringValue*>(v);
    }
    inline IntegerValue* geti(Value* v)
    {
        return static_cast<IntegerValue*>(v);
    }
    inline BoolValue* getb(Value* v)
    {
        return static_cast<BoolValue*>(v);
    }
    inline WindowValue* getw(Value* v)
    {
        return static_cast<WindowValue*>(v);
    }

    inline FloatValue* getf(Value* v)
    {
        return static_cast<FloatValue*>(v);
    }
    
    template <typename T>
    inline std::vector<Value*> convertToValue(std::vector<T> data)
    {
        throw std::runtime_error("Can not convert '" + std::string(typeid(T).name()) + "' to List.\n");
    }
    template <>
    inline std::vector<Value*> convertToValue<Value*>(std::vector<Value*> data)
    {
        return data;
    }
    template <>
    inline std::vector<Value*> convertToValue<int>(std::vector<int> data)
    {
        std::vector<Value*> result(data.size());
        std::transform(data.begin(), data.end(), result.begin(), 
                       [](int x){return new IntegerValue(x);});
        return result;
    }
    template <>
    inline std::vector<Value*> convertToValue<float>(std::vector<float> data)
    {
        std::vector<Value*> result(data.size());
        std::transform(data.begin(), data.end(), result.begin(), 
                       [](float x){return new FloatValue(x);});
        return result;
    }
    template <>
    inline std::vector<Value*> convertToValue<bool>(std::vector<bool> data)
    {
        std::vector<Value*> result(data.size());
        std::transform(data.begin(), data.end(), result.begin(), 
                       [](bool x){return new BoolValue(x);});
        return result;
    }
    template <>
    inline std::vector<Value*> convertToValue<std::string>(std::vector<std::string> data)
    {
        std::vector<Value*> result(data.size());
        std::transform(data.begin(), data.end(), result.begin(), 
                       [](std::string x){return new StringValue(x);});
        return result;
    }
    
}
#endif