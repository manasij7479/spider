#include <iostream>
#include "CppGen.hpp"
#include "AST/AST.hpp"
#include "Parser/Stream.hpp"
#include "Parser/ParseUtils.hpp"
// // using namespace spider::cppgen;

int main()
{
     spider::Stream stream("\n\twhile\nwhilewhile while(1){}\nwhile");
     spider::MatchExact while_k("while");
     spider::MatchZeroOrMore many_whiles(&while_k);
     std::cout<<many_whiles(stream)<<"\n";
     std::cout<<many_whiles.count()<<"\n";
     std::cout<<stream.get();
} 

