#ifndef SPIDER_USER_TYPES_HPP
#define SPIDER_USER_TYPES_HPP
#include <graph/graph.hpp>
namespace spider
{
    namespace user
    {
        typedef graph::Graph<int,int> Graph;
        typedef int Integer;
        typedef float Real;
        typedef std::string String;
    }
}
#endif