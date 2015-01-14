#include "Runtime/Functions.hpp"
#include "BuiltinTypeOperations.hpp"
#include "GraphOperations.hpp"
#include "WindowOperations.hpp"
namespace spider
{
    std::map<std::string, Function> FunctionMap = 
    {
        {"add_int", add_int},
        {"insert_vertex", insert_vertex},
        {"insert_edge", insert_edge},
        {"remove_vertex", remove_vertex},
        {"remove_edge", remove_edge},
        {"order", order},
        {"generate", generate},
        {"make_win", make_win}
    };
}