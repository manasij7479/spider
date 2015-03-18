#ifndef SPIDER_RUNTIME_FUNCTION_HPP
#define SPIDER_RUNTIME_FUNCTION_HPP
#include <functional>
#include <map>
#include <vector>
#include "Runtime/UserFunction.hpp"
namespace spider
{
    class SymbolTable;
    class Value;
    class FunctionSystem
    {
        typedef std::function<Value*(std::vector<Value*>)> Function;
    public:
        FunctionSystem();
        bool isFunction(std::string name);

        Value* call(std::string name, std::vector<Value*> values, FunctionSystem& f, SymbolTable& table);
        void def(std::vector<std::string>, Statement* block);
    private:
        std::map<std::string, Function> FunctionMap;
        std::map<std::string, UserFunction> UserFunctionMap;
    };
    

}
#endif