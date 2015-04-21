#ifndef SPIDER_RUNTIME_TYPE_HPP
#define SPIDER_RUNTIME_TYPE_HPP
#include <string>
#include <map>
#include <vector>
#include <functional>
#include <QtWidgets>
/**
 * \brief Type.hpp - header file that contains all the datatyped defined in the language
 * **/
namespace spider
{
	/**
	 * \brief Value contains the different datatypes that will be supported by the language.
	 * It maps the names of the datatypes to their types. It does not define any functionality
	 * of the datatypes.
	 * **/
    class Value : public QObject
    {
        Q_OBJECT
    public:
    /** \brief - contains all the names of the different datatype **/
        enum class Type 
        {
            Void,
            Integer, String, Bool, Float,
            Graph, Window,
            List, Dict,
            Vattr, Eattr, 
            Any, Function
        };
        /**
         * \brief - Constructor
         * 
         * @param Type t - Parameter, a datatype supported by the language
         * **/
        Value(Type t):type(t){};
        /** \brief - Destructor **/
        virtual ~Value(){}
        /** \brief - function to show "<Empty Value>" **/
        virtual std::string show() {return "<Empty Value>";};
        virtual void read(std::string s){throw std::runtime_error("Read operation not supported.");};
        Type type;
        /**
         * \brief - to map datatype name to the actual datatype
         * **/
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
                {"vattr", Type::Vattr},
                {"any", Type::Any},
                {"func", Type::Function}
                //Add the rest as needed
            };
        }
        /**
         * \brief - to map the actual datatype to the datatype name
         * **/
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
                { Type::Vattr, "vattr"},
                { Type::Any, "any"},
                { Type::Function, "func"}
                //Add the rest as needed
            };
        }
        /** \brief - to neglect previous changes **/
        void changeCallback(){emit changed();}
    signals:
        void changed();
    };
    using VType = Value::Type;
    /**
     * \brief IntegerValue returns the value of an integer declared
     * using the Integer datatype supported by the language
     * **/
    class IntegerValue : public Value
    {
    public:
        IntegerValue(int i):Value(VType::Integer),data(i){}
        std::string show()
        {
            return std::to_string(data);
        }
        void read(std::string s)
        {
            data = std::stoi(s);
        }
        int data;
    };
    /**
     * \brief BoolValue returns the value of an integer declared
     * using the Boolean datatype supported by the language
     * **/
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
        void read(std::string s)
        {
            if (s == "true")
                data = true;
            else data = false;
        }
        bool data;
    };
    /**
     * \brief StringValue returns the value of an integer declared
     * using the String datatype supported by the language
     * **/
    class StringValue : public Value
    {
    public:
        StringValue(std::string s):Value(VType::String),data(s){}
        std::string show()
        {
            return data;
        }
        void read(std::string s)
        {
            data = s;
        }
        std::string data;
    };
    /**
     * \brief FloatValue returns the value of an integer declared
     * using the Float datatype supported by the language
     * **/
    class FloatValue : public Value
    {
    public:
        FloatValue(float f):Value(VType::Float), data(f){}
        std::string show()
        {
            return std::to_string(data);
        }
        void read(std::string s)
        {
            data = std::stof(s);
        }
        float data;
    };
    /**
     * \brief VoidValue returns nothing. It is a class declared to tackle
     * all Void variables declared using the Void datatype supported by the
     * language.
     * **/
    class VoidValue: public Value //contains nothing
    {
    public:
        VoidValue():Value(VType::Void){};
    };

}
#endif
