#ifndef SPIDER_RUNTIME_HPP
#define SPIDER_RUNTIME_HPP
#include "Runtime/Type.hpp"
#include "Runtime/SymbolTable.hpp"
#include "Runtime/Functions.hpp"
#include "Runtime/Statement.hpp"
namespace spider
{
    class Runtime
    {
    public:
        Runtime(SymbolTable t = SymbolTable(), bool nested_mode_ = false);
        void eval(std::vector<std::string> args);
        void eval(Statement& stmt);
        Value* getFromSymbolTable(std::string name);
    private:
        bool tryShow(std::string idf);
        bool tryDeclare(std::string idf, std::string type, std::string value);
        bool tryAssign(std::string idf, std::string value);
        
        bool tryCall(std::vector<std::string> args);
        void assignPrev(Value* x);
        Value* constructValue(VType type, std::string value);
        Value* constructValue(std::string value);
        //TODO: Add other builtins here
        Value* constructLiteral(VType type, std::string value);
        Value* constructLiteral(std::string str);
        std::vector<Value*> substituteArgs(std::vector<std::string> args);
        Value* prev;
        Value* prev_to_prev;
        SymbolTable table;
        FunctionSystem functions;
        bool breakflag;
        bool nested_mode;

    };
}
#endif
/*
Test code:
1. Loop from 10 to 6:
let x int i10
let b bool true
while b
{
    show x
    add x i-1
    assign x _
    equal x i5
    if _
    {
        break
    }
    greater x i0
    assign b _
}
exit

2. Simple function returning its input:
function foo result int input int
{
    let result int input 
}
foo i7479
show _
 
*/