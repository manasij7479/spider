#include <iostream>
#include "CppGen.hpp"
#include "AST/AST.hpp"
#include "Parser/Stream.hpp"
#include "Parser/Matchers.hpp"
#include "Parser/ParseUtils.hpp"
#include "Parser/SpiderParser.hpp"
// // using namespace spider::cppgen;
using namespace spider;
int main()
{
    spider::Stream stream("f1oo4barbar");
//     auto matcher = *Cat(Alpha(),Star(Alnum()));
//     auto a = Direct("foo");
//     auto b = Direct("bar");
//     Match& matcher = *Cat(a,Star(b));
//     
//     std::cout<<matcher(stream)<<std::endl;
//     std::cout<<stream.pos();
    
    spider::MatchSpiderIdentifier idf;
    std::cout<<idf(stream)<<std::endl;
    std::cout<<idf.get();
    
    
} 

