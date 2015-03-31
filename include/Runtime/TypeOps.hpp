#ifndef SPIDER_TYPE_OPS_HPP
#define SPIDER_TYPE_OPS_HPP
#include "Runtime/Type.hpp"
#include "Runtime/GraphValue.hpp"
#include "Runtime/WindowValue.hpp"
#include "Runtime/ListValue.hpp"
#include <algorithm>
namespace spider
{
    inline void assert_type(Value* x, VType t)
    {
        if ( t != VType::Any && x->type != t)
            throw std::runtime_error("Type Mismatch: Expected: '"+Value::TypeToNameMap()[t]+"'. Got: '"+Value::TypeToNameMap()[x->type]+"' \n");
    }
    template <typename T>
    void assert_size(std::vector<T> args, uint size, std::string reason = "<>")
    {
        if (args.size() != size)
            throw std::runtime_error("Size Mismatch."+reason+"\n");
    }
    template <typename T>
    void assert_size(std::vector<T> args, std::function<bool(uint)> predicate, std::string reason = "<>")
    {
        if (predicate(args.size()) == false)
            throw std::runtime_error("Size Mismatch."+reason+"\n");
    }

    inline std::function<bool(uint)> greater(int i)
    {
        return [i](int x){return x > i;};
    }
    inline std::function<bool(uint)> lesser(int i)
    {
        return [i](int x){return x < i;};
    }
    inline std::function<bool(uint)> greater_eq(int i)
    {
        return [i](int x){return x >= i;};
    }
    inline std::function<bool(uint)> lesser_eq(int i)
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
    inline ListValue* getl(Value* v)
    {
        return static_cast<ListValue*>(v);
    }
    inline DictValue* getd(Value* v)
    {
        return static_cast<DictValue*>(v);
    }
    inline VattrValue* getv(Value* v)
    {
        return static_cast<VattrValue*>(v);
    }
    
    
    template <typename T>
    inline Value* convertToValue(T t)
    {
        throw std::runtime_error("Can not convert '" + std::string(typeid(T).name()) + "' to Value.\n");
    }
    template <>
    inline Value* convertToValue<Value*>(Value* data)
    {
        return data;
    }
    template <>
    inline Value* convertToValue<int>(int data)
    {
        return new IntegerValue(data);
    }
    template <>
    inline Value* convertToValue<float>(float data)
    {
        return new FloatValue(data);
    }
    template <>
    inline Value* convertToValue<bool>(bool data)
    {
        return new BoolValue(data);
    }
    template <>
    inline Value* convertToValue<std::string>(std::string data)
    {
        return new StringValue(data);
    }
    
    template <typename T>
    inline std::vector<Value*> convertToCompoundValue(const std::vector<T>& data)
    {
        std::vector<Value*> result(data.size());
        std::transform(data.begin(), data.end(), result.begin(), 
                    [](T x){return convertToValue(x);});
        return result;
        
    }
    template <typename K , typename T>
    inline std::map<K, Value*> convertToCompoundValue(const std::map<K, T>& data)
    {
        std::map<K, Value*> result;
        for(auto p : data)
            result.insert({p.first, convertToValue(p.second)});
        return result;
    }
    
    template <typename T>
    inline Value* convertToValue(std::vector<T> data)
    {
        return new ListValue(convertToCompoundValue(data));
    }
    template <typename T>
    inline Value* convertToValue(const std::map<std::string, T>& data)
    {
        return new DictValue(convertToCompoundValue(data));
    }
    template <typename T>
    inline Value* convertToValue(const std::map<int, T>& data)
    {
        return new VattrValue(convertToCompoundValue(data));
    }
    
    
    
}
#endif