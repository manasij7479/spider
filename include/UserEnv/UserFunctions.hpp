#ifndef SPIDER_USER_FUNCTIONS
#define SPIDER_USER_FUNCTIONS
#include <graph/graph.hpp>
#include <UserEnv/UserTypes.hpp>
#include <UserEnv/SymbolTable.hpp>
//These functions may only take and return types specified in UserTypes.
namespace spider
{
    namespace user
    {
        void testFunction(){std::cout<<"WORKS";}
    }
}
#endif