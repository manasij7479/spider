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
        Runtime(spider::SymbolTable t = SymbolTable(), spider::FunctionSystem f = FunctionSystem(), bool nested_mode_ = false);
        void eval(std::vector<std::string> args);
        void eval(Statement& stmt);
        Value* getFromSymbolTable(std::string name);
        FunctionSystem& getFunctions();
    private:
        bool tryShow(std::vector<std::string> idf, char sep = '\n');
        bool tryDeclare(std::string idf, std::string type, std::vector<std::string> value);
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

3. Factorial !
function factorial f int n int
{
    let f int i1
    lesser n i2
    if _
    {
        break
    }
    sub n i1
    factorial _
    mul n _
    assign f _
}
factorial i5
show _

4. Function with a loop:
function foo x int n int
{
    let x int i1
    while true
    {
        show x
        add x i1 
        assign x _
        greater x n
        if _
        {
            break
        }
    }
}
foo i10

*/