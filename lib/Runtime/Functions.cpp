#include "NewRuntime/Functions.hpp"
#include "BuiltinTypeOperations.hpp"
#include "GraphOperations.hpp"
#include "WindowOperations.hpp"
namespace spider
{
    std::map<std::string, Function> FunctionMap = 
    {
        {"add_int", add_int},
        {"insert_vertex", insert_vertex},
        {"order", order},
        {"std_graph", std_graph},
        {"make_window", make_window}
    };
}