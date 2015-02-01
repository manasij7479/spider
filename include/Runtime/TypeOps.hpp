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
    inline Value* convertToValue(T x)
    {
        throw std::runtime_error("Can not convert '" + std::string(typeid(T).name()) + "' to Value.");
    }
    
    template<>
    inline Value* convertToValue<int>(int x)
    {
        return new IntegerValue(x);
    }
    template<>
    inline Value* convertToValue<float>(float x)
    {
        return new FloatValue(x);
    }
    template<>
    inline Value* convertToValue<bool>(bool x)
    {
        return new BoolValue(x);
    }
    template<>
    inline Value* convertToValue<std::string>(std::string x)
    {
        return new StringValue(x);
    }
    template<>
    inline Value* convertToValue<Value*>(Value* x)
    {
        return x;
    }
    
    
    template <typename T>
    inline std::vector<Value*> convertVectorToValue(std::vector<T> data)
    {
        std::vector<Value*> result(data.size());
        std::transform(data.begin(), data.end(), result.begin(), convertToValue<T>);
        return result;
    }
    
    
    
}
#endif