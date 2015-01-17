#include "Runtime/Functions.hpp"
#include "BuiltinTypeOperations.hpp"
#include "GraphOperations.hpp"
#include "WindowOperations.hpp"

#define  MAP(x) {#x, x}
#define IMAP(x) {#x, int_##x}
#define FMAP(x) {#x, float_##x}
#define GMAP(x) {#x, graph_##x}
#define BMAP(x) {#x, bool_##x}
#define WMAP(x) {#x, win_##x}
namespace spider
{
    FunctionSystem::FunctionSystem()
    {
        FunctionMap = 
        {
            //Integer Functions
            IMAP(add), IMAP(greater), IMAP(lesser), IMAP(equal),
            
            //Float Functions
            FMAP(addf), FMAP(greaterf), FMAP(lesserf), FMAP(equalf),
            
            //Boolean Functions
            BMAP(or), BMAP(and), BMAP(not),
            
            //Graph Functions
            GMAP(insert_vertex), GMAP(insert_edge), GMAP(remove_vertex), GMAP(remove_edge),
            GMAP(order), GMAP(generate),GMAP(union), GMAP(intersection), GMAP(join),
            GMAP(symmetric_difference), GMAP(cartesian_product), GMAP(complement),
            GMAP(edge_deletion_subgraph), GMAP(vertex_deletion_subgraph),
            GMAP(edge_contraction_minor), GMAP(size), GMAP(out_degree), GMAP(in_degree),
            GMAP (degree), GMAP(nregular), GMAP(radius), GMAP(diameter), GMAP(density), 
            GMAP(is_vertex), GMAP(is_adjacent), GMAP(is_subgraph), GMAP(is_spanning_subgraph),
            GMAP(is_cyclic), GMAP(is_connected), GMAP(is_vertex_pair_connected), GMAP(is_complement), 
            GMAP(is_complete), GMAP(is_sparse), GMAP(is_empty), GMAP(is_edgeless),
            GMAP(is_tree), GMAP(is_centre), GMAP(is_periphery), GMAP(is_eulerian), 
            GMAP(is_semi_eulerian), GMAP(is_component), GMAP(is_regular), 
            
            //Window Functions
            WMAP(display), WMAP(change_layout)
        };
    }
}
