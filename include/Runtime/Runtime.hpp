#ifndef SPIDER_RUNTIME_HPP
#define SPIDER_RUNTIME_HPP
#include "Runtime/Type.hpp"
#include "Runtime/TypeOps.hpp"
#include "Runtime/SymbolTable.hpp"
#include "Runtime/Functions.hpp"
#include <iostream>
#include <sstream>
#include "Runtime/GraphValue.hpp"
#include "Runtime/WindowValue.hpp"
#include "Runtime/Statement.hpp"
namespace spider
{
    class Runtime
    {
    public:
        Runtime()
        {
            prev_to_prev = prev = new VoidValue();
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
                    throw std::runtime_error("Calling Function '"+args[0]+"' Failed.\n");
            }
            else 
            { // make call keyword optional, may be removed later
                auto it = FunctionMap.find(args[0]);
                if (it != FunctionMap.end())
                {
                    if(tryCall(args) == false)
                        throw std::runtime_error("Calling Function '"+args[0]+"' Failed.\n");
                }
                else 
                    throw std::runtime_error("Bad keyword: '"+args[0]+"'.\n");
            }
        }
        void eval(Statement& stmt)
        {
            if (stmt.isBlock() == false)
                eval(stmt.getSingle());
            else 
            {
                for (auto inner_stmt : stmt.getBlock())
                    eval(*inner_stmt);
            }
        }
    private:
        bool tryShow(std::string idf)
        {
            Value* x;
            if (idf == "_")
                x = prev;
            else if (idf == "__")
                x = prev_to_prev;
            else
                x= table.get(idf);
            if (x == nullptr)
                return false;
            std::cout<<x->show()<<std::endl;
//             assignPrev(x);
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
//             std::cout << x->show()<<std::endl;
            prev_to_prev = prev;
            prev = x;
        }
        Value* constructValue(VType type, std::string value)
        {
            Value* result;
            if(value == "_")
                result = prev;
            else if (value == "__")
                result = prev_to_prev;
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
                case VType::Integer : return new IntegerValue(std::stoi(value.substr(1, value.length()-1)));
                case VType::String : return new StringValue(value.substr(1, value.length()-2));
                case VType::Bool : return new BoolValue(((value == "true")? true: false));
                case VType::Float : return new FloatValue(std::stof(value.substr(1, value.length()-1)));
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
            if (str[0] == 'f')
                return new FloatValue(std::stof(str.substr(1, str.length())));
            if (str[0] == 'i')
                return new IntegerValue(std::stoi(str.substr(1, str.length())));
            else throw std::runtime_error("Can not parse Literal Value.\n");
        }
        std::vector<Value*> substituteArgs(std::vector<std::string> args)
        {
            std::vector<Value*> result;
            for(auto arg: args)
            {
                Value* x;
                if (arg == "_")
                    result.push_back(prev);
                else if (arg == "__")
                    result.push_back(prev_to_prev);
                else if ((x=table.get(arg)) != nullptr)
                    result.push_back(x);
                else 
                    result.push_back(constructLiteral(arg));
            }
            return result;
        }
        Value* prev;
        Value* prev_to_prev;
        SymbolTable table;
    };
}
#endif
/*
 Test code:
 
let x int i10
label loop
show x
add x i-1
assign x _
greater x i0
if _ loop
 
 */