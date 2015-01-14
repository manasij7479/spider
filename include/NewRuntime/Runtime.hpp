#ifndef SPIDER_RUNTIME_HPP
#define SPIDER_RUNTIME_HPP
#include "Type.hpp"
#include "SymbolTable.hpp"
#include "Functions.hpp"
#include <iostream>
#include <sstream>
#include "GraphValue.hpp"
#include "WindowValue.hpp"
namespace spider
{
    class Runtime
    {
    public:
        Runtime()
        {
            prev = new VoidValue();
        }
        void eval(std::vector<std::string> args)
        {
            if (args[0] == "show")
            {
                assert_size(args, 2);
                if(tryShow(args[1]) == false)
                    throw std::runtime_error("Object : '"+args[1]+"' does not exist.\n");
            }
            else if (args[0] == "let")
            {
                assert_size(args, 4);
                if (tryDeclare(args[1], args[2], args[3]) == false)
                    throw std::runtime_error("Declaration Failed.\n");
            }
            else if (args[0] == "assign")
            {
                assert_size(args, 3);
                if (tryAssign(args[1], args[2]) == false)
                    throw std::runtime_error("Assignment Failed.\n");
            }
            else if (args[0] == "call")
            {
                assert_size(args, greater_eq(2));
                args.erase(args.begin());
                if(tryCall(args) == false)
                    throw std::runtime_error("Function Call Failed.\n");
            }
            else 
            { // make call keyword optional, may be removed later
                auto it = FunctionMap.find(args[0]);
                if (it != FunctionMap.end())
                    if(tryCall(args) == false)
                        throw std::runtime_error("Function Call Failed.\n");
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
            //TODO Handle type-value mismatch
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
        
        bool tryCall(std::vector<std::string> args)
        {
            std::string fname = args[0];
            args.erase(args.begin());
            auto callArgs = substituteArgs(args);
            auto it = FunctionMap.find(fname);
            if (it == FunctionMap.end())
                return false;
            auto result = (it->second)(callArgs);
            assignPrev(result);
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
                result = prev;
            else
                result = table.get(value);
            if (result == nullptr)
                return constructLiteral(type, value);
            assert_type(result, type);
            return result;
        }
        
        //TODO: Add other builtins here
        Value* constructLiteral(VType type, std::string value)
        {
            switch(type)
            {
                case VType::Integer : return new IntegerValue(std::stoi(value));
                case VType::String : return new StringValue(value.substr(1, value.length()-2));
                case VType::Bool : return new BoolValue(((value == "true")? true: false));
                default: return nullptr;
            }
        }
        Value* constructLiteral(std::string str)
        {
            if (str[0] == '"' && str[str.length()-1]=='"')
                return new StringValue(str.substr(1, str.length()-2));
            if (str == "true")
                return new BoolValue(true);
            if (str == "false")
                return new BoolValue(false);
            else return new IntegerValue(std::stoi(str));
            //TODO float support
        }
        std::vector<Value*> substituteArgs(std::vector<std::string> args)
        {
            std::vector<Value*> result;
            for(auto arg: args)
            {
                Value* x;
                if (arg == "_")
                    result.push_back(prev);
                else if ((x=table.get(arg)) != nullptr)
                    result.push_back(x);
                else 
                    result.push_back(constructLiteral(arg));
            }
            return result;
        }
        Value* prev;
        SymbolTable table;
    };
}
#endif