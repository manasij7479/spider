#include <iostream>
#include "CppGen.hpp"

using namespace spider::cpp;
int main()
{
    
    auto stmt = 
    new WhileStmt
        (new Literal("true"),
            new StmtBlock(
                {new StandaloneExprStmt(new FunctionCallExpr("foo",{}))}
            ));
    std::cout<< stmt;
    
} 