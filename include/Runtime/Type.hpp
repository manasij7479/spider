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
            Integer, String, Bool, Float,
            Graph, Window
        };
        Value(Type t):type(t){};
        virtual std::string show() {return "<Empty Value>";};
        Type type;
    };
    using VType = Value::Type;
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
    class FloatValue : public Value
    {
    public:
        FloatValue(float f):data(f), Value(VType::Float){}
        std::string show()
        {
            return std::to_string(data);
        }
        float data;
    };
    class VoidValue: public Value //contains nothing
    {
    public:
        VoidValue():Value(VType::Void){};
    };

}
#endif