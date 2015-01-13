#ifndef SPIDER_RUNTIME_TYPE_HPP
#define SPIDER_RUNTIME_TYPE_HPP
namespace spider
{
    class Value
    {
    public:
        enum class Type {Integer, String, Bool, Real, Graph, Window};
        Value(Type t):type(t){};
        virtual std::string show() {return "<Empty Value>";};
        Type type;
    };
    using VType = Value::Type;
    
    class IntegerValue : public Value
    {
    public:
        IntegerValue(int i):data(i),Value(VType::Integer){}
        int data;
    };
    
    class StringValue : public Value
    {
    public:
        StringValue(std::string s):data(s),Value(VType::String){}
        std::string data;
    };
    
    
    
}
#endif