#ifndef SPIDER_RUNTIME_TYPE_HPP
#define SPIDER_RUNTIME_TYPE_HPP
#include <string>
#include <map>
#include <vector>
#include <functional>
namespace spider
{
    class Value
    {
    public:
        enum class Type 
        {
            Void,
            Integer, String, Bool, Real,
            Graph, Window
        };
        Value(Type t):type(t){};
        virtual std::string show() {return "<Empty Value>";};
        Type type;
    };
    using VType = Value::Type;
    std::map<std::string, VType> NameToTypeMap = 
    {
        {"int", VType::Integer},
        {"string", VType::String},
        {"bool", VType::Bool}
        //Add the rest as needed
    };
    void assert_type(Value* x, VType t)
    {
        if (x->type != t)
            throw std::runtime_error("Type Mismatch.\n");
    }
    void assert_size(std::vector<Value*> args, int size)
    {
        if (args.size() != size)
            throw std::runtime_error("Size Mismatch.\n");
    }
    void assert_size(std::vector<Value*> args, std::function<bool(int)> predicate)
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
    
    class IntegerValue : public Value
    {
    public:
        IntegerValue(int i):data(i),Value(VType::Integer){}
        std::string show()
        {
            return std::to_string(data);
        }
        int data;
    };
    
    class BoolValue : public Value
    {
    public:
        BoolValue(bool b):data(b),Value(VType::Bool){}
        std::string show()
        {
            if (data == true)
                return "true";
            else return "false";
        }
        bool data;
    };
    
    class StringValue : public Value
    {
    public:
        StringValue(std::string s):data(s),Value(VType::String){}
        std::string show()
        {
            return data;
        }
        std::string data;
    };
    
    class VoidValue: public Value //contains nothing
    {
    public:
        VoidValue():Value(VType::Void){};
    };
    
}
#endif