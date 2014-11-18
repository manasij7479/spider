#ifndef SPIDER_USER_SYMBOL_TABLES_HPP
#define SPIDER_USER_SYMBOL_TABLES_HPP
#include "UserEnv/UserTypes.hpp"
#include <map>
#include <string>

//Every Type in UserTypes must have a map here

namespace spider
{
    class SymbolTable
    {
    public:
        std::map<std::string, user::Graph>      GraphMap;
        std::map<std::string, user::Integer>    IntegerMap;
        std::map<std::string, user::Real>       RealMap;
        std::map<std::string, user::String>     StringMap;
    };
}
#endif