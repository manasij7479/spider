#ifndef SPIDER_TYPE_OPS_HPP
#define SPIDER_TYPE_OPS_HPP
#include "Runtime/Type.hpp"
#include "Runtime/GraphValue.hpp"
#include "Runtime/WindowValue.hpp"
namespace spider
{

    std::map<std::string, VType> NameToTypeMap = 
    {
        {"int", VType::Integer},
        {"string", VType::String},
        {"bool", VType::Bool},
        {"float", VType::Float},
        {"graph", VType::Graph},
        {"window", VType::Window}
        //Add the rest as needed
    };
    std::map<VType, std::string> TypeToNameMap = 
    {
        { VType::Integer, "int"},
        { VType::String, "string"},
        { VType::Bool, "bool"},
        { VType::Float, "float"},
        { VType::Graph, "graph"},
        { VType::Window, "window"}
        //Add the rest as needed
    };
    
    
    
    void assert_type(Value* x, VType t)
    {
        if (x->type != t)
            throw std::runtime_error("Type Mismatch: Expected: '"+TypeToNameMap[t]+"'. Got: '"+TypeToNameMap[x->type]+"' \n");
    }
    template <typename T>
    void assert_size(std::vector<T> args, int size)
    {
        if (args.size() != size)
            throw std::runtime_error("Size Mismatch.\n");
    }
    template <typename T>
    void assert_size(std::vector<T> args, std::function<bool(int)> predicate)
    {
        if (predicate(args.size()) == false)
            throw std::runtime_error("Size Mismatch.\n");
    }

    std::function<bool(int)> greater(int i)
    {
        return [i](int x){return x > i;};
    }
    std::function<bool(int)> lesser(int i)
    {
        return [i](int x){return x < i;};
    }
    std::function<bool(int)> greater_eq(int i)
    {
        return [i](int x){return x >= i;};
    }
    std::function<bool(int)> lesser_eq(int i)
    {
        return [i](int x){return x <= i;};
    }
    
    
    GraphValue* getg(Value* v)
    {
        return static_cast<GraphValue*>(v);
    }
    StringValue* gets(Value* v)
    {
        return static_cast<StringValue*>(v);
    }
    IntegerValue* geti(Value* v)
    {
        return static_cast<IntegerValue*>(v);
    }
    BoolValue* getb(Value* v)
    {
        return static_cast<BoolValue*>(v);
    }
    WindowValue* getw(Value* v)
    {
        return static_cast<WindowValue*>(v);
    }
    FloatValue* getf(Value* v)
    {
        return static_cast<FloatValue*>(v);
    }
}
#endif