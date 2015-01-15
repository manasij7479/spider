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
        
        //Integer Functions
        FMAP(addf), FMAP(greaterf), FMAP(lesser), FMAP(equal),
        
        //Boolean Functions
        BMAP(or), BMAP(and), BMAP(not),
        
        //Graph Functions
        GMAP(insert_vertex), GMAP(insert_edge), GMAP(remove_vertex), GMAP(remove_edge),
        GMAP(order), GMAP(generate),GMAP(union), GMAP(intersection), GMAP(join),
        GMAP(symmetric_difference), GMAP(cartesian_product), GMAP(complement),
        GMAP(edge_deletion_subgraph), GMAP(vertex_deletion_subgraph),
        GMAP(edge_contraction_minor), GMAP(size_), GMAP(out_degree), GMAP(in_degree),
        GMAP (degree), GMAP(nregular), GMAP(radius), GMAP(diameter), GMAP(density), 
        
        //Window Functions
        WMAP(display), WMAP(change_layout)
    };
}
