#include <iostream>
#include "CppGen.hpp"
using namespace spider::cppgen;
int main()
{
    
    auto stmt = 
    new IfStmt
        (   new BinExpr(new Literal("5"),new Literal("6"),new BinOp("<")),
            new StmtBlock(
                {new StandaloneExprStmt(new FunctionCallExpr("foo",{}))}),
            new StmtBlock(
                {new StandaloneExprStmt(new FunctionCallExpr("bar",{}))}) 
        );
    std::cout<< stmt;   
} 

