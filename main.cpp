#include <iostream>
#include "CppGen.hpp"
#include "AST/AST.hpp"
#include "Parser/Stream.hpp"
#include "Parser/ParseUtils.hpp"
// // using namespace spider::cppgen;

int main()
{
    spider::Stream stream("else\nif     while\twhilewhilewhilewhile");
    spider::MatchExact while_k("while");
    spider::MatchExact if_k("if");
    spider::MatchExact else_k("else");
    spider::MatchZeroOrMore many_whiles(&while_k);
     
    spider::MatchAll all({&else_k, &if_k, &many_whiles});

    std::cout<<all(stream)<<"\n";
    std::cout<<many_whiles.count()<<"\n";
    std::cout<<stream.peek()<<"\n\n";
    
} 

