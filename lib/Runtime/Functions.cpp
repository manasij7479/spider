#include "Runtime/Functions.hpp"
#include "BuiltinTypeOperations.hpp"
#include "GraphOperations.hpp"
#include "WindowOperations.hpp"

#define  MAP(x) {#x, x}
#define IMAP(x) {#x, int_##x}
#define GMAP(x) {#x, graph_##x}
#define BMAP(x) {#x, bool_##x}
#define WMAP(x) {#x, win_##x}
namespace spider
{
    std::map<std::string, Function> FunctionMap = 
    {
        //Integer Functions
        IMAP(add), IMAP(greater), IMAP(lesser), IMAP(equal),
        
        //Boolean Functions
        BMAP(or), BMAP(and), BMAP(not),
        
        //Graph Functions
        GMAP(insert_vertex), GMAP(insert_edge), GMAP(remove_vertex), GMAP(remove_edge),
        GMAP(order), GMAP(generate),GMAP(union), GMAP(intersection), GMAP(join),
        GMAP(symmetric_difference), GMAP(cartesian_product), GMAP(complement),
        GMAP(edge_deletion_subgraph), GMAP(vertex_deletion_subgraph),
        GMAP(edge_contraction_minor),
        
        //Window Functions
        WMAP(display), WMAP(change_layout)
    };
}