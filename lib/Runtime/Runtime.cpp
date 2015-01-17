#include "Runtime/Runtime.hpp"
#include <iostream>
#include <sstream>
#include "Runtime/GraphValue.hpp"
#include "Runtime/WindowValue.hpp"
#include "Runtime/TypeOps.hpp"
namespace spider
{
    Runtime::Runtime(SymbolTable t, bool nested_mode_) : table(t)
    {
        prev_to_prev = prev = new VoidValue();
        breakflag = false;
        nested_mode = nested_mode_;
    }
    void Runtime::eval(std::vector<std::string> args)
    {
        if (args[0] == "show")
        {
            assert_size(args, 2);
            if(tryShow(args[1]) == false)
                throw std::runtime_error("Object : '"+args[1]+"' does not exist.\n");
        }
        else if (args[0] == "exit")
            exit(0);
        else if (args[0] == "break")
            breakflag = true;
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
            if (functions.isFunction(args[0]))
            {
                if(tryCall(args) == false)
                    throw std::runtime_error("Calling Function '"+args[0]+"' Failed.\n");
            }
            else 
                throw std::runtime_error("Bad keyword: '"+args[0]+"'.\n");
        }
    }
    void Runtime::eval(Statement& stmt)
    {
        if (stmt.hasTail())
        {
            auto command = stmt.getSingle();
            assert_size(command, greater_eq(2));
            if (command[0] == "if")
            {
                BoolValue* cond = getb(constructValue(VType::Bool, command[1]));
                if (cond->data == true)
                    eval(*(stmt.getTail()));
            }
            else if (command[0] == "while")
            {
                while (true)
                {
                    BoolValue* cond = getb(constructValue(VType::Bool, command[1]));
                    if (cond->data == false)
                        break;
                    else if (breakflag == true)
                    {
                        breakflag = false;
                        break;
                    }
                    else eval(*(stmt.getTail())); 
                }
            }
            else if (command[0] == "function")
                functions.def(command, stmt.getTail());
        }
        else if (stmt.isBlock() == false)
            eval(stmt.getSingle());
        else 
        {
            if (!nested_mode )
                table.push(); // for local variables
            for (auto inner_stmt : stmt.getBlock())
            {
//                     std::cout<<breakflag<<std::endl;
                if (breakflag == true)
                    break;
                eval(*inner_stmt);
            }
            if (!nested_mode)
            table.pop();
        }
    }
    Value* Runtime::getFromSymbolTable(std::string name)
    {
        return table.get(name);
    }
    
    bool Runtime::tryShow(std::string idf)
    {
        Value* x = constructValue(idf);
        std::cout<<x->show()<<std::endl;
//             assignPrev(x);
        return true;
    }
    bool Runtime::tryDeclare(std::string idf, std::string type, std::string value)
    {
        //TODO Handle type-value mismatch
        Value* x = table.local_get(idf);
        if (x != nullptr)
            return false;
        else
        {
            x = constructValue(Value::NameToTypeMap()[type], value);
            table.insert(idf, x);
            assignPrev(x);
            return true;
        }
    }
    bool Runtime::tryAssign(std::string idf, std::string value)
    {
        Value* x = table.get(idf);
        if (x == nullptr)
            return false;
        x = constructValue(x->type, value);
        table.modify(idf, x);
        assignPrev(x);
        return true;
    }
    
    bool Runtime::tryCall(std::vector<std::string> args)
    {
        std::string fname = args[0];
        args.erase(args.begin());
        auto callArgs = substituteArgs(args);
        if (functions.isFunction(fname) == false)
            return false;
        auto result = functions.call(fname, callArgs, table);
        assignPrev(result);
        return true;
    }
    
    void Runtime::assignPrev(Value* x)
    {
//             std::cout << x->show()<<std::endl;
        prev_to_prev = prev;
        prev = x;
    }
    Value* Runtime::constructValue(VType type, std::string value)
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
    Value* Runtime::constructValue(std::string value)
    {
        Value* result;
        if(value == "_")
            result = prev;
        else if (value == "__")
            result = prev_to_prev;
        else
            result = table.get(value);
        if (result == nullptr)
            return constructLiteral(value);
        return result;
    }
    //TODO: Add other builtins here
    Value* Runtime::constructLiteral(VType type, std::string value)
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
    Value* Runtime::constructLiteral(std::string str)
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
    std::vector<Value*> Runtime::substituteArgs(std::vector<std::string> args)
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
    
}