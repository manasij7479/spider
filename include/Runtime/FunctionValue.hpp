#ifndef SPIDER_RUNTIME_USER_FUNCTION_HPP
#define SPIDER_RUNTIME_USER_FUNCTION_HPP
#include <vector>
#include <string>
#include "Runtime/Type.hpp"

namespace spider
{
    class Statement;
    class SymbolTable;
    class Runtime;
    typedef std::function<Value*(std::vector<Value*>)> Function;
    std::map< std::string, Function >& getInbuiltFunctions();
    
    class FunctionValue : public Value
    {
    public:
        FunctionValue(std::string name_) : Value(VType::Function) , name(name_){};
        
        virtual Value* call(std::vector<Value*> args)=0;
        std::string show(){return "Placeholder:" + name;}
    private:
        std::string name;
        
    };
    
    class UserDefinedFunction : public FunctionValue
    {
    public:
        UserDefinedFunction(std::vector<std::string> proto, Statement* block_, Runtime* runtime);
        Value* call(std::vector<Value*> args);
    private:
        Statement* block;
        std::vector<std::pair<std::string, VType>> formal_params;
        std::pair<std::string, VType> return_idf;
        Runtime* RT;
    };
    
    class InbuiltFunction : public FunctionValue
    {
    public:
        InbuiltFunction(std::string name_, Function f_);
        Value* call(std::vector<Value*> args);
    private:
        Function f;
    };
}
#endif