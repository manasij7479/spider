#ifndef SPIDER_RUNTIME_TYPE_HPP
#define SPIDER_RUNTIME_TYPE_HPP
#include <string>
#include <map>
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
        {"string", VType::String}
        //Add the rest as needed
    };
    void assert_type(Value* x, VType t)
    {
        if (x->type != t)
            throw std::runtime_error("Type Mismatch.\n");
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
    
    class VoidType: public Value
    {
    public:
        VoidType():Value(VType::Void){};
    };
    
}
#endif