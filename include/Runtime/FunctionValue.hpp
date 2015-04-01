#ifndef SPIDER_RUNTIME_USER_FUNCTION_HPP
#define SPIDER_RUNTIME_USER_FUNCTION_HPP
#include <vector>
#include <string>
#include "Runtime/Type.hpp"

namespace spider
{
    class Statement;
    class SymbolTable;
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
        UserDefinedFunction(std::vector<std::string> proto, Statement* block_, SymbolTable* table_);
        Value* call(std::vector<Value*> args);
    private:
        Statement* block;
        std::vector<std::pair<std::string, VType>> formal_params;
        std::pair<std::string, VType> return_idf;
        SymbolTable* table;
    };
}
#endif