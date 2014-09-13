#include <iostream>
#include "CppGen.hpp"
#include "AST/AST.hpp"
#include "Parser/Stream.hpp"
#include "Parser/ParseUtils.hpp"
// // using namespace spider::cppgen;

int main()
{
    spider::Stream stream("elseifwhilewhilewhilewhilewhile");
    spider::MatchExact while_k("while");
    spider::MatchExact if_k("if");
    spider::MatchExact else_k("else");
    spider::MatchZeroOrMore many_whiles(&while_k);
     
    spider::MatchAny wie({&many_whiles, &while_k, &if_k, &else_k});
     
     
    std::cout<<wie(stream)<<"\n";
    std::cout<<wie.which()<<"\n";
    std::cout<<stream.peek()<<"\n"<<many_whiles.count()<<"\n\n";
    many_whiles.reset();
    
    std::cout<<wie(stream)<<"\n";
    std::cout<<wie.which()<<"\n";
    std::cout<<stream.peek()<<"\n"<<many_whiles.count()<<"\n\n";
    many_whiles.reset(); 
    
    std::cout<<wie(stream)<<"\n";
    std::cout<<wie.which()<<"\n";
    std::cout<<stream.peek()<<"\n"<<many_whiles.count()<<"\n\n";
    many_whiles.reset();
} 

