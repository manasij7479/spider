#include <iostream>
#include "CppGen.hpp"
#include "AST/AST.hpp"
#include "Parser/Stream.hpp"
#include "Parser/ParseUtils.hpp"
// // using namespace spider::cppgen;

int main()
{
     spider::Stream stream("\n\twhile(true)");
     spider::MatchExact while_k("while");
     std::cout<<while_k(stream)<<"\n";
     std::cout<<stream.get();
} 

