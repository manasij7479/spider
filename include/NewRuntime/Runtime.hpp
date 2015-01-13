#ifndef SPIDER_RUNTIME_HPP
#define SPIDER_RUNTIME_HPP
#include "Type.hpp"
#include "SymbolTable.hpp"
#include <iostream>
namespace spider
{
    class Runtime
    {
    public:
        Runtime()
        {
            prev = new VoidType();
        }
        void eval(std::vector<std::string> args)
        {
            if (args[0] == "show")
            {
                if(tryShow(args[1]) == false)
                    throw std::runtime_error("Object : '"+args[1]+"' does not exist.\n");
            }
            else if (args[0] == "let")
            {
                if (tryDeclare(args[1], args[2], args[3]) == false)
                    throw std::runtime_error("Declaration Failed.\n");
            }
            else if (args[0] == "assign")
            {
                if (tryAssign(args[1], args[2]) == false)
                    throw std::runtime_error("Assignment failed.\n");
            }
        }
    private:
        bool tryShow(std::string idf)
        {
            Value* x;
            if (idf == "_")
                x = prev;
            else
                x= table.get(idf);
            if (x == nullptr)
                return false;
            std::cout<<x->show()<<std::endl;
            assignPrev(x);
            return true;
        }
        bool tryDeclare(std::string idf, std::string type, std::string value)
        {
            Value* x = table.get(idf);
            if (x != nullptr)
                return false;
            else
            {
                x = constructValue(NameToTypeMap[type], value);
                table.insert(idf, x);
                assignPrev(x);
                return true;
            }
        }
        bool tryAssign(std::string idf, std::string value)
        {
            Value* x = table.get(idf);
            if (x == nullptr)
                return false;
            x = constructValue(x->type, value);
            table.modify(idf, x);
            assignPrev(x);
            return true;
        }
        void assignPrev(Value* x)
        {
            prev = x;
        }
        Value* constructValue(VType type, std::string value)
        {
            Value* result;
            if(value == "_")
                return prev;
            else if ((result = table.get(value))!=nullptr)
                return result;
            else return constructLiteral(type, value);
            // Move these into a table somewhere
        }
        Value* constructLiteral(VType type, std::string value)
        {
            switch(type)
            {
                case VType::Integer : return new IntegerValue(std::stoi(value));
                case VType::String : return new StringValue(value);
                default: return nullptr;
            }
        }
        Value* prev;
        SymbolTable table;
    };
}
#endif