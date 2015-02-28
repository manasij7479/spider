#ifndef SPIDER_RUNTIME_HPP
#define SPIDER_RUNTIME_HPP
#include "Runtime/Type.hpp"
#include "Runtime/SymbolTable.hpp"
#include "Runtime/Functions.hpp"
#include "Runtime/Statement.hpp"
#include <functional>
namespace spider
{
    class Runtime
    {
    public:
        Runtime(spider::SymbolTable t = SymbolTable(), spider::FunctionSystem f = FunctionSystem(), bool nested_mode_ = false);
        void eval(std::vector<std::string> args);
        void eval(Statement& stmt);
        Value* getFromSymbolTable(std::string name);
        FunctionSystem& getFunctions();
        void setShowCallback(std::function<void(std::string)> f);
    private:
        bool tryShow(std::vector<std::string> idf, char sep = ' ');
        bool tryDeclare(std::string idf, std::vector<std::string> value);
        bool tryAssign(std::string idf, std::vector<std::string> value);
        
        bool tryCall(std::string fname, std::vector<std::string> value);
        void assignPrev(Value* x);
        Value* constructValue(VType type, std::string value);
        Value* constructValue(std::string value);
        Value* constructLiteral(VType type, std::string value);
        Value* constructLiteral(std::string str);
        std::vector<Value*> substituteArgs(std::vector<std::string> args);
        Value* prev;
        Value* prev_to_prev;
        SymbolTable table;
        FunctionSystem functions;
        bool breakflag;
        bool nested_mode;
        std::function<void(std::string)> showCallback;
///TODO: Idea for List impl.
//Remove most construct* functions
//Make substituteArgs more sophisticated and return a LIstValue*
//Make the rest of try* functions use the list returned by substituteArgs (rename it btw) 
        
    };
}
#endif
/*
Test code:
1. Loop from 10 to 6:
let x i10
let b true
while b
{
    show x
    assign x sub x i1
    equal x i5
    if _
    {
        break
    }
    assign b greater x i0
}
exit

2. Simple function returning its input:
function foo result int input int
{
    let result input 
}
foo i7479
show _

3. Factorial !
function factorial f int n int
{
    let f i1
    lesser n i2
    if _
    {
        break
    }
    sub n i1
    factorial _
    assign f mul n _
}
factorial i5
show _

4. Function with a loop:
function foo x int n int
{
    let x i1
    while true
    {
        show x
        assign x add x i1 
        greater x n
        if _
        {
            break
        }
    }
}
foo i10

*/