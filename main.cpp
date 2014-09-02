#include <iostream>
#include "CppGen.hpp"
 
int main()
{
    std::cout<<spider::cpp::WhileStmt(new spider::cpp::Literal("true"),new spider::cpp::Stmt()).str();
    
}