#include "Runtime/Functions.hpp"
#include "BuiltinTypeOperations.hpp"
#include "GraphOperations.hpp"
#include "WindowOperations.hpp"
namespace spider
{
    std::map<std::string, Function> FunctionMap = 
    {
        {"add_int", add_int},
        {"insert_vertex", graph_insert_vertex},
        {"insert_edge", graph_insert_edge},
        {"remove_vertex", graph_remove_vertex},
        {"remove_edge", graph_remove_edge},
        {"order", graph_order},
        {"generate", graph_generate},
        {"union",graph_union},
        {"intersection",graph_intersection},
        {"join",graph_join},
        {"symmetric_difference",graph_symmetric_difference},
        {"cartesian_product",graph_cartesian_product},
        {"complement",graph_complement},
        {"edge_deletion_subgraph",graph_edgedeletionsubgraph},
        {"vertex_deletion_subgraph",graph_vertexdeletionsubgraph},
        {"edge_contractionminor",graph_edgecontractionminor},
        {"make_win", make_win}
    };
}