#include "Runtime/Functions.hpp"
#include "BuiltinTypeOperations.hpp"
#include "GraphOperations.hpp"
#include "WindowOperations.hpp"

#include "Runtime/Type.hpp"
#include "Runtime/Statement.hpp"
#include "Runtime/SymbolTable.hpp"
#include "Runtime/TypeOps.hpp"

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
            IMAP(sub), IMAP(mul), IMAP(mod), IMAP(div),
            
            //Float Functions
            FMAP(addf), FMAP(greaterf), FMAP(lesserf), FMAP(equalf),
            FMAP(mulf), FMAP(subf), FMAP(divf),
            
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
            GMAP(bfs_animate), GMAP(dfs_animate),
            //Window Functions
            WMAP(display), WMAP(change_layout)
        };
    }
    bool FunctionSystem::isFunction(std::string name)
    {
        return (FunctionMap.find(name) != FunctionMap.end()) ||
               (UserFunctionMap.find(name) != UserFunctionMap.end());
    }
    Value* FunctionSystem::call(std::string name, std::vector<Value*> values, FunctionSystem& f)
    {
        if (! isFunction(name))
            throw std::runtime_error("Calling Function '"+name+"' Failed.\n");
        if (FunctionMap.find(name) != FunctionMap.end())
            return FunctionMap[name](values);
        else return UserFunctionMap[name].call(values, f);
    }
    void FunctionSystem::def(std::vector<std::string> proto, Statement* block)
    {
        UserFunctionMap[proto[1]] = UserFunction(proto, block);
    }
}
