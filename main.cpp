#include <iostream>
#include "CppGen.hpp"
#include "AST/AST.hpp"
#include "Parser/Stream.hpp"
#include "Parser/ParseUtils.hpp"
// // using namespace spider::cppgen;

int main()
{
    spider::Stream stream("bcd1");
    spider::MatchCharClass alpha('a','z');
    spider::MatchOneOrMore alphastar(&alpha);
    std::cout<<alphastar(stream);
    std::cout<<' '<<alphastar.count();
    
} 

