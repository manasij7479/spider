#include "graph/graph.hpp"
#include "graph/util/generate.hpp"
#include "graph/algorithm/operations.hpp"
#include "graph/algorithm/enumeration.hpp"
#include "graph/algorithm/search.hpp"
#include "graph/algorithm/mst.hpp"
#include "Runtime/Type.hpp"
#include "Runtime/TypeOps.hpp"
#include "Runtime/GraphValue.hpp"
#include "Runtime/WindowValue.hpp"
#include "Layout/CircularLayout.hpp"
#include "Layout/TreeLayout.hpp"
#include <chrono>
#include <thread>
namespace spider
{
    Value* graph_insert_vertex(std::vector<Value*> args)
    {
        assert_size(args, 2);
        assert_type(args[0], VType::Graph);
        assert_type(args[1], VType::String);
        auto g = getg(args[0]);
        auto v = gets(args[1]);
        g->data->insertVertex(v->data);
        g->changeCallback();
        return g;
    }
    Value* graph_remove_vertex(std::vector<Value*> args)
    {
        assert_size(args, 2);
        assert_type(args[0], VType::Graph);
        assert_type(args[1], VType::String);
        auto g = getg(args[0]);
        auto v = gets(args[1]);
        g->data->removeVertex(v->data);
        g->changeCallback();
        return g;
    }
    Value* graph_insert_edge(std::vector<Value*> args)
    {
        assert_size(args, 4);
        assert_type(args[0], VType::Graph);
        assert_type(args[1], VType::String);
        assert_type(args[2], VType::String);
        assert_type(args[3], VType::Integer);
        auto g = getg(args[0]);
        auto x = static_cast<StringValue*>(args[1]);
        auto y = static_cast<StringValue*>(args[2]);
        auto e = static_cast<IntegerValue*>(args[3]);
        
        g->data->insertEdge(x->data, y->data, e->data);
        g->changeCallback();
        return g;
    }
    
    Value* graph_remove_edge(std::vector<Value*> args)
    {
        assert_size(args, 3);
        assert_type(args[0], VType::Graph);
        assert_type(args[1], VType::String);
        assert_type(args[2], VType::String);
        auto g = getg(args[0]);
        auto x = gets(args[1]);
        auto y = gets(args[2]);
        
        g->data->removeEdge(x->data, y->data);
        g->changeCallback();
        return g;
    }
    
    
    Value* graph_order(std::vector<Value*> args)
    {
        assert_size(args, 1);
        assert_type(args[0], VType::Graph);
        return new IntegerValue(getg(args[0])->data->order());
    }
    typedef std::function<graph::AdjacencyList<std::string,int>(std::vector<int>, int)> F;
    std::map<std::string, F> GraphNameMap()
    {
        return {
            {"empty", graph::gen::empty},
            {"path", graph::gen::path},
            {"cycle", graph::gen::cycle},
            {"complete", graph::gen::complete},
            {"wheel", graph::gen::wheel},
            {"complete_bipartite", graph::gen::complete_bipartite},
            {"star", graph::gen::star},
            {"star_polygon", graph::gen::star_polygon},
            {"friendship", graph::gen::friendship},
            {"mobius_ladder", graph::gen::mobius_ladder},
            {"grid", graph::gen::grid},
            {"generalized_petersen", graph::gen::generalized_petersen},
            {"k_ary_tree", graph::gen::k_ary_tree},
            {"wagner", graph::gen::wagner},
            {"butterfly", graph::gen::butterfly},
            {"petersen", graph::gen::petersen},
            {"durer", graph::gen::durer},
            {"desargues", graph::gen::desargues},
            {"mobius_kantor", graph::gen::mobius_kantor},
            {"dodecahedron", graph::gen::dodecahedron},
            {"nauru", graph::gen::nauru},
        };
    }
    
    Value* graph_generate(std::vector<Value*> args)
    {
        assert_size(args, greater_eq(1));
        assert_type(args[0], VType::String);
        std::vector<int> newArgs;
        for(int i = 1; i < args.size(); ++i)
        {
            assert_type(args[i], VType::Integer);
            newArgs.push_back(geti(args[i])->data);
        }
        auto g  = new GraphValue::Graph(
            GraphNameMap()[gets(args[0])->data](newArgs, 1));
        return new GraphValue(g);
    }
    
    Value* graph_union(std::vector<Value*> args)
    {
        assert_size(args, 2);
        assert_type(args[0], VType::Graph);
        assert_type(args[1], VType::Graph);
        
        auto g = new GraphValue::Graph(graph::Union(*(getg(args[0])->data), *(getg(args[1])->data)));
        return new GraphValue(g);
    }
    
    
    Value* graph_intersection(std::vector<Value*> args)
    {
        assert_size(args, 2);
        assert_type(args[0], VType::Graph);
        assert_type(args[1], VType::Graph);
        
        auto g = new GraphValue::Graph(graph::intersection(*(getg(args[0])->data), *(getg(args[1])->data)));
        return new GraphValue(g);
    }
    
    
    Value* graph_join(std::vector<Value*> args)
    {
        assert_size(args, 2);
        assert_type(args[0], VType::Graph);
        assert_type(args[1], VType::Graph);
        
        auto g = new GraphValue::Graph(graph::join(*(getg(args[0])->data), *(getg(args[1])->data)));
        return new GraphValue(g);
    }
    
    Value* graph_symmetric_difference(std::vector<Value*> args)
    {
        assert_size(args, 2);
        assert_type(args[0], VType::Graph);
        assert_type(args[1], VType::Graph);
        
        auto g = new GraphValue::Graph(graph::symmetric_difference(*(getg(args[0])->data), *(getg(args[1])->data)));
        return new GraphValue(g);
    }
    
    Value* graph_cartesian_product(std::vector<Value*> args)
    {
        assert_size(args, 2);
        assert_type(args[0], VType::Graph);
        assert_type(args[1], VType::Graph);
        
        auto g = new GraphValue::Graph(graph::cartesian_product(*(getg(args[0])->data), *(getg(args[1])->data)));
        return new GraphValue(g);
    }
    
    Value* graph_complement(std::vector<Value*> args)
    {
        assert_size(args, 1);
        assert_type(args[0], VType::Graph);
        
        auto g = new GraphValue::Graph(graph::complement(*(getg(args[0])->data)));
        return new GraphValue(g);
    }
    
    Value* graph_edge_deletion_subgraph(std::vector<Value*> args)
    {
        assert_size(args, 3);
        assert_type(args[0], VType::Graph);
        assert_type(args[1], VType::String);
        assert_type(args[2], VType::String);
        
        auto x = gets(args[1]);
        auto y = gets(args[2]);
        
        auto g = new GraphValue::Graph(graph::EdgeDeletionSubgraph(*(getg(args[0])->data), x->data, y->data));
        return new GraphValue(g);
    }
    
    Value* graph_vertex_deletion_subgraph(std::vector<Value*> args)
    {
        assert_size(args, 2);
        assert_type(args[0], VType::Graph);
        assert_type(args[1], VType::String);
        
        auto x = gets(args[1]);
        
        auto g = new GraphValue::Graph(graph::VertexDeletionSubgraph(*(getg(args[0])->data), x->data));
        return new GraphValue(g);
    }
    
    Value* graph_edge_contraction_minor(std::vector<Value*> args)
    {
        assert_size(args, 3);
        assert_type(args[0], VType::Graph);
        assert_type(args[1], VType::String);
        assert_type(args[2], VType::String);
        
        auto x = gets(args[1]);
        auto y = gets(args[2]);
        
        auto g = new GraphValue::Graph(graph::EdgeContractionMinor(*(getg(args[0])->data), x->data, y->data));
        return new GraphValue(g);
    }
    
    Value* graph_size(std::vector<Value*> args)
    {
        assert_size(args, 1);
        assert_type(args[0], VType::Graph);
                
        return new IntegerValue(graph::Size(*(getg(args[0])->data)));
    }
    
    Value* graph_out_degree(std::vector<Value*> args)
    {
        assert_size(args, 2);
        assert_type(args[0], VType::Graph);
        assert_type(args[1], VType::String);
        
        auto x = gets(args[1]);
                
        return new IntegerValue(graph::outDegree(*(getg(args[0])->data), x->data));
    }
    
    Value* graph_in_degree(std::vector<Value*> args)
    {
        assert_size(args, 2);
        assert_type(args[0], VType::Graph);
        assert_type(args[1], VType::String);
        
        auto x = gets(args[1]);
                
        return new IntegerValue(graph::inDegree(*(getg(args[0])->data), x->data));
    }
    
    Value* graph_degree(std::vector<Value*> args)
    {
        assert_size(args, 2);
        assert_type(args[0], VType::Graph);
        assert_type(args[1], VType::String);
        
        auto x = gets(args[1]);
                
        return new IntegerValue(graph::degree(*(getg(args[0])->data), x->data));
    }
    
    Value* graph_nregular(std::vector<Value*> args)
    {
        assert_size(args, 1);
        assert_type(args[0], VType::Graph);
                
        return new IntegerValue(graph::nregular(*(getg(args[0])->data)));
    }
    
    Value* graph_radius(std::vector<Value*> args)
    {
        assert_size(args, 1);
        assert_type(args[0], VType::Graph);
                
        return new IntegerValue(graph::Radius(*(getg(args[0])->data)));
    }
    
    Value* graph_diameter(std::vector<Value*> args)
    {
        assert_size(args, 1);
        assert_type(args[0], VType::Graph);
                
        return new IntegerValue(graph::Radius(*(getg(args[0])->data)));
    }
    
    Value* graph_density(std::vector<Value*> args)
    {
        assert_size(args, 1);
        assert_type(args[0], VType::Graph);
                
        return new FloatValue(graph::Density(*(getg(args[0])->data)));
    }
    
    Value* graph_is_vertex(std::vector<Value*> args)
    {
        assert_size(args, 2);
        assert_type(args[0], VType::Graph);
        assert_type(args[1], VType::String);
        return new BoolValue(graph::isVertex(*(getg(args[0])->data), gets(args[1])->data));
    }
		
    Value* graph_is_adjacent(std::vector<Value*> args)
    {
        assert_size(args, 3);
        assert_type(args[0], VType::Graph);
        assert_type(args[1], VType::String);
        assert_type(args[2], VType::String);
        return new BoolValue(graph::isAdjacent(*(getg(args[0])->data), 
                                               gets(args[1])->data, 
                                               gets(args[2])->data));
    }
        
    Value* graph_is_subgraph(std::vector<Value*> args)
    {
        assert_size(args, 2);
        assert_type(args[0], VType::Graph);
        assert_type(args[1], VType::Graph);
        return new BoolValue(graph::isSubgraph(*(getg(args[0])->data), *(getg(args[1])->data)));
    }
        
    Value* graph_is_spanning_subgraph(std::vector<Value*> args)
    {
        assert_size(args, 2);
        assert_type(args[0], VType::Graph);
        assert_type(args[1], VType::Graph);
        return new BoolValue(graph::isSpanningSubgraph(*(getg(args[0])->data), *(getg(args[1])->data)));
    }
        
    Value* graph_is_connected(std::vector<Value*> args)
    {
        assert_size(args, 1);
        assert_type(args[0], VType::Graph);
        return new BoolValue(graph::isConnected(*(getg(args[0])->data)));
    }
        
    Value* graph_is_vertex_pair_connected(std::vector<Value*> args)
    {
        assert_size(args, 3);
        assert_type(args[0], VType::Graph);
        assert_type(args[1], VType::String);
        assert_type(args[2], VType::String);
        return new BoolValue(graph::isConnected(*(getg(args[0])->data), 
                                                gets(args[1])->data, 
                                                gets(args[2])->data));
    }
        
    Value* graph_is_component(std::vector<Value*> args)
    {
        assert_size(args, 2);
        assert_type(args[0], VType::Graph);
        assert_type(args[1], VType::Graph);
        return new BoolValue(graph::isComponent(*(getg(args[0])->data), *(getg(args[1])->data)));
        }
        
    Value* graph_is_regular(std::vector<Value*> args)
    {
        assert_size(args, 1);
        assert_type(args[0], VType::Graph);
        return new BoolValue(graph::isRegular(*(getg(args[0])->data)));
        }
        
    Value* graph_is_eulerian(std::vector<Value*> args)
    {
        assert_size(args, 1);
        assert_type(args[0], VType::Graph);
        return new BoolValue(graph::isEulerian(*(getg(args[0])->data)));
    }
        
    Value* graph_is_semi_eulerian(std::vector<Value*> args)
    {
        assert_size(args, 1);
        assert_type(args[0], VType::Graph);
        return new BoolValue(graph::isSemiEulerian(*(getg(args[0])->data)));
    }
        
    Value* graph_is_complete(std::vector<Value*> args)
    {
        assert_size(args, 1);
        assert_type(args[0], VType::Graph);
        return new BoolValue(graph::isComplete(*(getg(args[0])->data)));
    }
        
    Value* graph_is_cyclic(std::vector<Value*> args)
    {
        assert_size(args, 1);
        assert_type(args[0], VType::Graph);
        return new BoolValue(graph::isCyclic(*(getg(args[0])->data)));
    }
        
    Value* graph_is_edgeless(std::vector<Value*> args)
    {
        assert_size(args, 1);
        assert_type(args[0], VType::Graph);
        return new BoolValue(graph::isEdgeless(*(getg(args[0])->data)));
    }
        
    Value* graph_is_complement(std::vector<Value*> args)
    {
        assert_size(args, 2);
        assert_type(args[0], VType::Graph);
        assert_type(args[1], VType::Graph);
        return new BoolValue(graph::isComplement(*(getg(args[0])->data), *(getg(args[1])->data)));
    }
        
    Value* graph_is_sparse(std::vector<Value*> args)
    {
        assert_size(args, 1);
        assert_type(args[0], VType::Graph);
        return new BoolValue(graph::isSparse(*(getg(args[0])->data)));
    }
        
    Value* graph_is_tree(std::vector<Value*> args)
    {
        assert_size(args, 1);
        assert_type(args[0], VType::Graph);
        return new BoolValue(graph::isTree(*(getg(args[0])->data)));
    }
        
    Value* graph_is_empty(std::vector<Value*> args)
    {
        assert_size(args, 1);
        assert_type(args[0], VType::Graph);
        return new BoolValue(graph::isEmpty(*(getg(args[0])->data)));
        }
        
    Value* graph_is_centre(std::vector<Value*> args)
    {
        assert_size(args, 2);
        assert_type(args[0], VType::Graph);
        assert_type(args[1], VType::String);
        return new BoolValue(graph::isCentre(*(getg(args[0])->data), gets(args[1])->data));
    }
        
    Value* graph_is_periphery(std::vector<Value*> args)
    {
        assert_size(args, 2);
        assert_type(args[0], VType::Graph);
        assert_type(args[1], VType::String);
        return new BoolValue(graph::isPeriphery(*(getg(args[0])->data), gets(args[1])->data));
    }
    
    Value* graph_bfs_animate(std::vector<Value*> args)
    {
        assert_size(args, 2);
        assert_type(args[0], VType::Graph);
        assert_type(args[1], VType::String);
        auto g = new graph::AdjacencyList<std::string, int>();
        auto gv = new GraphValue(g);
        std::string s = gets(args[1])->data;
        g->insertVertex(s);
        WindowValue* win = new WindowValue(gv, new TreeLayout<graph::AdjacencyList<std::string, int>>(*g, s));
        graph::BreadthFirstSearch<graph::AdjacencyList<std::string, int>> bfs(*getg(args[0])->data, s);
        bfs.setp4([&](const std::string& x,const std::string& y)
        {
            g->insertVertex(y);
            g->insertEdge(x, y, 1);
            gv->changeCallback();
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            return true;
        });
        bfs();
        return gv;
    }
    Value* graph_dfs_animate(std::vector<Value*> args)
    {
        assert_size(args, 2);
        assert_type(args[0], VType::Graph);
        assert_type(args[1], VType::String);
        auto g = new graph::AdjacencyList<std::string, int>();
        auto gv = new GraphValue(g);
        std::string s = gets(args[1])->data;
        g->insertVertex(s);
        WindowValue* win = new WindowValue(gv, new TreeLayout<graph::AdjacencyList<std::string, int>>(*g, s));
        graph::DepthFirstSearch<graph::AdjacencyList<std::string, int>> bfs(*getg(args[0])->data, s);
        bfs.setp4([&](const std::string& x,const std::string& y)
        {
            g->insertVertex(y);
            g->insertEdge(x, y, 1);
            gv->changeCallback();
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            return true;
        });
        bfs();
        return gv;
    }
    Value* graph_kruskal_animate(std::vector<Value*> args)
    {
        assert_size(args, 1);
        assert_type(args[0], VType::Graph);
        auto g = new graph::AdjacencyList<std::string, int>();
        auto gv = new GraphValue(g);
        WindowValue* win = new WindowValue(gv, new CircularLayout<graph::AdjacencyList<std::string, int>>(*g));
        auto state = graph::Kruskal(*getg(args[0])->data, [&](const std::string& x,const std::string& y, int w)
        {
            g->insertVertex(x);
            g->insertVertex(y);
            g->insertEdge(x, y, w);
            gv->changeCallback();
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            return true;
        });
        return gv;
    }
}
