#include "NewRuntime/Functions.hpp"
#include "BuiltinTypeOperations.hpp"
#include "GraphOperations.hpp"
namespace spider
{
    std::map<std::string, Function> FunctionMap = 
    {
        {"add_int", add_int},
        {"insert_vertex", insert_vertex},
        {"std_graph", std_graph}
    };
}