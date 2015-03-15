#ifndef SPIDER_RUNTIME_TYPE_HPP
#define SPIDER_RUNTIME_TYPE_HPP
#include <string>
#include <map>
#include <vector>
#include <functional>
#include <QObject>
namespace spider
{
    class Value : public QObject
    {
        Q_OBJECT
    public:
        enum class Type 
        {
            Void,
            Integer, String, Bool, Float,
            Graph, Window,
            List, Dict,
            Vattr, Eattr
        };
        Value(Type t):type(t){};
        virtual ~Value(){}
        virtual std::string show() {return "<Empty Value>";};
        Type type;
        static std::map<std::string, Type> NameToTypeMap()
        {
            return  
            {
                {"int", Type::Integer},
                {"string", Type::String},
                {"bool", Type::Bool},
                {"float", Type::Float},
                {"graph", Type::Graph},
                {"window", Type::Window},
                {"list", Type::List},
                {"dict", Type::Dict},
                {"vattr", Type::Vattr}
                //Add the rest as needed
            };
        }
        
        static std::map<Type, std::string> TypeToNameMap()
        {
            return 
            {
                { Type::Integer, "int"},
                { Type::String, "string"},
                { Type::Bool, "bool"},
                { Type::Float, "float"},
                { Type::Graph, "graph"},
                { Type::Window, "window"},
                { Type::List, "list"},
                { Type::Dict, "dict"},
                { Type::Vattr, "vattr"}
                //Add the rest as needed
            };
        }
        void changeCallback(){emit changed();}
    signals:
        void changed();
    };
    using VType = Value::Type;
    class IntegerValue : public Value
    {
    public:
        IntegerValue(int i):Value(VType::Integer),data(i){}
        std::string show()
        {
            return std::to_string(data);
        }
        int data;
    };
    
    class BoolValue : public Value
    {
    public:
        BoolValue(bool b):Value(VType::Bool),data(b){}
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
        StringValue(std::string s):Value(VType::String),data(s){}
        std::string show()
        {
            return data;
        }
        std::string data;
    };
    class FloatValue : public Value
    {
    public:
        FloatValue(float f):Value(VType::Float), data(f){}
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