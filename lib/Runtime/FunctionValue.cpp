#include "Runtime/FunctionValue.hpp"
#include "Runtime/Runtime.hpp"
#include "Runtime/TypeOps.hpp"

#define  MAP(x) {#x, x}
#define IMAP(x) {#x, int_##x}
#define FMAP(x) {#x, float_##x}
#define GMAP(x) {#x, graph_##x}
#define BMAP(x) {#x, bool_##x}
#define WMAP(x) {#x, win_##x}
#define LMAP(x) {#x, list_##x}
#define DMAP(x) {#x, dict_##x}
#define EMAP(x) {#x, exp_##x}

#include "BuiltinTypeOperations.hpp"
#include "GraphOperations.hpp"
#include "WindowOperations.hpp"
#include "CompundTypeOperations.hpp"
#include "ExperimentalOperations.hpp"


namespace spider
{
    std::map<std::string, Function>& getInbuiltFunctions()
    {
        static std::map<std::string, Function> result = 
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
            GMAP(bfs_animate), GMAP(dfs_animate), GMAP(kruskal_animate),
            GMAP(set_graph_attribute), GMAP(get_graph_attribute),
            GMAP(set_vertex_attribute), GMAP(set_vertex_attribute_all),
            GMAP(get_vertex_attribute),
            GMAP(vertex_list), GMAP(degree_map), GMAP(vertex_coloring),
            //List Functions
            LMAP(create_list), LMAP(value_at),
            
            //Dict Fuctions
            DMAP(create_dict),
            
            //Window Functions
            WMAP(display), WMAP(change_layout),
            
            //Experimental
            EMAP(tree_rot_right), EMAP(tree_rot_left)
        };
        return result;
    }
    FunctionValue::FunctionValue(std::vector<std::string> proto, Statement* block_) : Value(VType::Function)
    {
        block = block_;
        assert_size(proto, greater_eq(4));// function keyword, name, return var, return
        assert_size(proto, [](int i){return i%2 == 0;}); // must be even
        name = proto[1];
        
        auto&& n_t_map =  Value::NameToTypeMap();
        
        return_idf = {proto[2],n_t_map[proto[3]]};
        for (uint i = 4; i < proto.size(); i+=2)
            formal_params.push_back({proto[i], n_t_map[proto[i+1]]});
    }
    Value* FunctionValue::call(std::vector<Value*> args, SymbolTable& table)
    {
        assert_size(args, formal_params.size());
        table.push();
        for(uint i = 0; i < args.size(); ++i)
        {
            assert_type(args[i], formal_params[i].second);
            table.insert(formal_params[i].first, args[i]);
        }
        Runtime nested(table, true);
        nested.eval(*block);
        Value* result = nested.getFromSymbolTable(return_idf.first);
        if (result == nullptr)
            throw std::runtime_error("Null return.\n");
        assert_type(result, return_idf.second);
//         std::cout << result->show() <<std::endl;
        table.pop();
        return result;
    }
        
}