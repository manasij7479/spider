#include "graph/graph.hpp"
#include "graph/util/generate.hpp"
#include "graph/algorithm/operations.hpp"
#include "graph/algorithm/enumeration.hpp"
#include "graph/algorithm/collections.hpp"
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
        assert_arg_list(args, 2, {VType::Graph, VType::Integer}, "insert_vertex");
        auto g = getg(args[0]);
        auto v = geti(args[1]);
        g->data->insertVertex(v->data);
        g->changeCallback();
        return g;
    }
    Value* graph_remove_vertex(std::vector<Value*> args)
    {
        assert_arg_list(args, 2, {VType::Graph, VType::Integer}, "remove_vertex");
        auto g = getg(args[0]);
        auto v = geti(args[1]);
        g->data->removeVertex(v->data);
        g->changeCallback();
        return g;
    }
    Value* graph_insert_edge(std::vector<Value*> args)
    {
        assert_arg_list(args, 4, {VType::Graph, VType::Integer, VType::Integer, VType::Integer}, "insert_edge");
        auto g = getg(args[0]);
        auto x = static_cast<IntegerValue*>(args[1]);
        auto y = static_cast<IntegerValue*>(args[2]);
        auto e = static_cast<IntegerValue*>(args[3]);
        
        g->data->insertEdge(x->data, y->data, e->data);
        g->changeCallback();
        return g;
    }
    
    Value* graph_remove_edge(std::vector<Value*> args)
    {
        assert_arg_list(args, 3, {VType::Graph, VType::Integer, VType::Integer}, "remove_edge");
        auto g = getg(args[0]);
        auto x = geti(args[1]);
        auto y = geti(args[2]);
        
        g->data->removeEdge(x->data, y->data);
        g->changeCallback();
        return g;
    }
    
    
    Value* graph_order(std::vector<Value*> args)
    {
        assert_arg_list(args, 1, {VType::Graph}, "order");
        return new IntegerValue(getg(args[0])->data->order());
    }
    typedef std::function<GraphValue::Graph(std::vector<int>, int)> F;
    std::map<std::string, F> GraphNameMap()
    {
        return {
            {"empty", graph::gen::empty},
            {"empty_directed", graph::gen::empty_directed},
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
            {"heawood",graph::gen::heawood},
            {"pappus",graph::gen::pappus},
            {"franklin",graph::gen::franklin},
            {"diamond",graph::gen::diamond},
            {"tietze",graph::gen::tietze},
            {"nauru", graph::gen::nauru},
        };
    }
    
    Value* graph_generate(std::vector<Value*> args)
    {
        assert_size(args, greater_eq(1));
        assert_type(args[0], VType::String);
        std::vector<int> newArgs;
        for(uint i = 1; i < args.size(); ++i)
        {
            assert_type(args[i], VType::Integer);
            newArgs.push_back(geti(args[i])->data);
        }
        auto g  = new GraphValue::Graph(
            GraphNameMap()[gets(args[0])->data](newArgs, 1));
        return new GraphValue(g);
    }
    
    Value* graph_get_GML_graph(std::vector<Value*> args)
    {
        assert_arg_list(args, 1, {VType::String}, "getGMLGraph");
        auto g = new GraphValue::Graph(graph::getGMLGraph((gets(args[0])->data)));
        return new GraphValue(g);
    }
    
    Value* graph_union(std::vector<Value*> args)
    {
        assert_arg_list(args, 2, {VType::Graph, VType::Graph}, "union");
        
        auto g = new GraphValue::Graph(graph::Union(*(getg(args[0])->data), *(getg(args[1])->data)));
        return new GraphValue(g);
    }
    
    
    Value* graph_intersection(std::vector<Value*> args)
    {
        assert_arg_list(args, 2, {VType::Graph, VType::Graph}, "intersection");
        auto g = new GraphValue::Graph(graph::intersection(*(getg(args[0])->data), *(getg(args[1])->data)));
        return new GraphValue(g);
    }
    
    
    Value* graph_join(std::vector<Value*> args)
    {
        assert_arg_list(args, 2, {VType::Graph, VType::Graph}, "join");
        
        auto g = new GraphValue::Graph(graph::join(*(getg(args[0])->data), *(getg(args[1])->data)));
        return new GraphValue(g);
    }
    
    Value* graph_symmetric_difference(std::vector<Value*> args)
    {
        assert_arg_list(args, 2, {VType::Graph, VType::Graph}, "symmetric_difference");
        auto g = new GraphValue::Graph(graph::symmetric_difference(*(getg(args[0])->data), *(getg(args[1])->data)));
        return new GraphValue(g);
    }
    
    Value* graph_cartesian_product(std::vector<Value*> args)
    {
        assert_arg_list(args, 2, {VType::Graph, VType::Graph}, "cartesian_product");
        
        auto g = new GraphValue::Graph(graph::cartesian_product(*(getg(args[0])->data), *(getg(args[1])->data)));
        return new GraphValue(g);
    }
    
    Value* graph_complement(std::vector<Value*> args)
    {
        assert_arg_list(args, 1, {VType::Graph}, "complement");
        auto g = new GraphValue::Graph(graph::complement(*(getg(args[0])->data)));
        return new GraphValue(g);
    }
    
    Value* graph_edge_deletion_subgraph(std::vector<Value*> args)
    {
        assert_arg_list(args, 3, {VType::Graph, VType::Integer, VType::Integer}, "edge_deletion_subgraph");
        auto x = geti(args[1]);
        auto y = geti(args[2]);
        
        auto g = new GraphValue::Graph(graph::EdgeDeletionSubgraph(*(getg(args[0])->data), x->data, y->data));
        return new GraphValue(g);
    }
    
    Value* graph_vertex_deletion_subgraph(std::vector<Value*> args)
    {
        assert_size(args, 2);
        assert_type(args[0], VType::Graph);
        assert_type(args[1], VType::Integer);
        assert_arg_list(args, 2, {VType::Graph, VType::Integer}, "vertex_deletion_subgraph");
        
        auto x = geti(args[1]);
        
        auto g = new GraphValue::Graph(graph::VertexDeletionSubgraph(*(getg(args[0])->data), x->data));
        return new GraphValue(g);
    }
    
    Value* graph_edge_contraction_minor(std::vector<Value*> args)
    {
        assert_arg_list(args, 3, {VType::Graph, VType::Integer, VType::Integer}, "edge_contraction_minor");
        
        auto x = geti(args[1]);
        auto y = geti(args[2]);
        
        auto g = new GraphValue::Graph(graph::EdgeContractionMinor(*(getg(args[0])->data), x->data, y->data));
        return new GraphValue(g);
    }
    
    Value* graph_size(std::vector<Value*> args)
    {
        assert_arg_list(args, 1, {VType::Graph}, "size");
                
        return new IntegerValue(graph::Size(*(getg(args[0])->data)));
    }
    
    Value* graph_out_degree(std::vector<Value*> args)
    {
        assert_arg_list(args, 2, {VType::Graph, VType::Integer}, "out_degree");
        auto x = geti(args[1]);
                
        return new IntegerValue(graph::outDegree(*(getg(args[0])->data), x->data));
    }
    
    Value* graph_in_degree(std::vector<Value*> args)
    {
        assert_arg_list(args, 2, {VType::Graph, VType::Integer}, "in_degree");   
        auto x = geti(args[1]);
                
        return new IntegerValue(graph::inDegree(*(getg(args[0])->data), x->data));
    }
    
    Value* graph_degree(std::vector<Value*> args)
    {
        assert_arg_list(args, 2, {VType::Graph, VType::Integer}, "degree");
        
        auto x = geti(args[1]);
                
        return new IntegerValue(graph::degree(*(getg(args[0])->data), x->data));
    }
    
    Value* graph_nregular(std::vector<Value*> args)
    {
        assert_arg_list(args, 1, {VType::Graph}, "nregular");
        
        return new IntegerValue(graph::nregular(*(getg(args[0])->data)));
    }
    
    Value* graph_radius(std::vector<Value*> args)
    {
        assert_arg_list(args, 1, {VType::Graph}, "radius");
                
        return new IntegerValue(graph::Radius(*(getg(args[0])->data)));
    }
    
    Value* graph_diameter(std::vector<Value*> args)
    {
        assert_arg_list(args, 1, {VType::Graph}, "diameter");
        return new IntegerValue(graph::Radius(*(getg(args[0])->data)));
    }
    
    Value* graph_density(std::vector<Value*> args)
    {
        assert_arg_list(args, 1, {VType::Graph}, "density");
        return new FloatValue(graph::Density(*(getg(args[0])->data)));
    }
    
    Value* graph_is_vertex(std::vector<Value*> args)
    {
        assert_arg_list(args, 2, {VType::Graph, VType::Integer}, "is_vertex");
        return new BoolValue(graph::isVertex(*(getg(args[0])->data), geti(args[1])->data));
    }
		
    Value* graph_is_adjacent(std::vector<Value*> args)
    {
        assert_arg_list(args, 3, {VType::Graph, VType::Integer, VType::Integer}, "is_adjacent");
        return new BoolValue(graph::isAdjacent(*(getg(args[0])->data), 
                                               geti(args[1])->data, 
                                               geti(args[2])->data));
    }
        
    Value* graph_is_subgraph(std::vector<Value*> args)
    {
        assert_arg_list(args, 2, {VType::Graph, VType::Graph}, "is_subgraph");
        return new BoolValue(graph::isSubgraph(*(getg(args[0])->data), *(getg(args[1])->data)));
    }
        
    Value* graph_is_spanning_subgraph(std::vector<Value*> args)
    {
        assert_arg_list(args, 2, {VType::Graph, VType::Graph}, "is_spanning_subgraph");
        return new BoolValue(graph::isSpanningSubgraph(*(getg(args[0])->data), *(getg(args[1])->data)));
    }
        
    Value* graph_is_connected(std::vector<Value*> args)
    {
        assert_arg_list(args, 1, {VType::Graph}, "is_connected");
        return new BoolValue(graph::isConnected(*(getg(args[0])->data)));
    }
        
    Value* graph_is_vertex_pair_connected(std::vector<Value*> args)
    {
        assert_arg_list(args, 3, {VType::Graph, VType::Integer, VType::Integer}, "is_vertex_pair_connected");
        return new BoolValue(graph::isConnected(*(getg(args[0])->data), 
                                                geti(args[1])->data, 
                                                geti(args[2])->data));
    }
        
    Value* graph_is_component(std::vector<Value*> args)
    {
        assert_arg_list(args, 2, {VType::Graph, VType::Graph}, "is_component");
        return new BoolValue(graph::isComponent(*(getg(args[0])->data), *(getg(args[1])->data)));
    }
        
    Value* graph_is_regular(std::vector<Value*> args)
    {
        assert_arg_list(args, 1, {VType::Graph}, "is_regular");
        return new BoolValue(graph::isRegular(*(getg(args[0])->data)));
        }
        
    Value* graph_is_eulerian(std::vector<Value*> args)
    {
        assert_arg_list(args, 1, {VType::Graph}, "is_eulerian");
        return new BoolValue(graph::isEulerian(*(getg(args[0])->data)));
    }
        
    Value* graph_is_semi_eulerian(std::vector<Value*> args)
    {
        assert_arg_list(args, 1, {VType::Graph}, "is_semi_eulerian");
        return new BoolValue(graph::isSemiEulerian(*(getg(args[0])->data)));
    }
        
    Value* graph_is_complete(std::vector<Value*> args)
    {
        assert_arg_list(args, 1, {VType::Graph}, "is_complete");
        return new BoolValue(graph::isComplete(*(getg(args[0])->data)));
    }
        
    Value* graph_is_cyclic(std::vector<Value*> args)
    {
        assert_arg_list(args, 1, {VType::Graph}, "is_cyclic");
        return new BoolValue(graph::isCyclic(*(getg(args[0])->data)));
    }
        
    Value* graph_is_edgeless(std::vector<Value*> args)
    {
        assert_arg_list(args, 1, {VType::Graph}, "is_edgeless");
        return new BoolValue(graph::isEdgeless(*(getg(args[0])->data)));
    }
        
    Value* graph_is_complement(std::vector<Value*> args)
    {
        assert_arg_list(args, 2, {VType::Graph, VType::Graph}, "is_complement");
        return new BoolValue(graph::isComplement(*(getg(args[0])->data), *(getg(args[1])->data)));
    }
        
    Value* graph_is_sparse(std::vector<Value*> args)
    {
        assert_arg_list(args, 1, {VType::Graph}, "is_sparse");
        return new BoolValue(graph::isSparse(*(getg(args[0])->data)));
    }
        
    Value* graph_is_tree(std::vector<Value*> args)
    {
        assert_arg_list(args, 1, {VType::Graph}, "is_tree");
        return new BoolValue(graph::isTree(*(getg(args[0])->data)));
    }
        
    Value* graph_is_empty(std::vector<Value*> args)
    {
        assert_arg_list(args, 1, {VType::Graph}, "is_empty");
        return new BoolValue(graph::isEmpty(*(getg(args[0])->data)));
    }
        
    Value* graph_is_centre(std::vector<Value*> args)
    {
        assert_arg_list(args, 2, {VType::Graph, VType::Integer}, "is_centre");
        return new BoolValue(graph::isCentre(*(getg(args[0])->data), geti(args[1])->data));
    }
        
    Value* graph_is_periphery(std::vector<Value*> args)
    {
        assert_arg_list(args, 2, {VType::Graph, VType::Integer}, "is_periphery");
        return new BoolValue(graph::isPeriphery(*(getg(args[0])->data), geti(args[1])->data));
    }
    
    Value* graph_bfs_animate(std::vector<Value*> args)
    {
        assert_arg_list(args, 2, {VType::Graph, VType::Integer}, "bfs_animate");
        auto g = new GraphValue::Graph();
        auto gv = new GraphValue(g);
        auto s = geti(args[1])->data;
        g->insertVertex(s);
        new WindowValue(gv, new TreeLayout(*gv, s));// FIXME: Leak
        graph::BreadthFirstSearch<GraphValue::Graph> bfs(*getg(args[0])->data, s);
        bfs.setp4([&](int x,int y)
        {
            g->insertVertex(y);
            g->insertEdge(x, y, 1);
            gv->changeCallback();
            QApplication::processEvents();
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            return true;
        });
        bfs();
        return gv;
    }
    Value* graph_bfs(std::vector<Value*> args)
    {
        assert_arg_list(args, 2, {VType::Graph, VType::Integer}, "bfs");
        auto g = new GraphValue::Graph();
        auto gv = new GraphValue(g);
        auto s = geti(args[1])->data;
        g->insertVertex(s);
        graph::BreadthFirstSearch<GraphValue::Graph> bfs(*getg(args[0])->data, s);
        bfs.setp4([&](int x,int y)
        {
            g->insertVertex(y);
            g->insertEdge(x, y, 1);
            return true;
        });
        bfs();
        return gv;
    }
    Value* graph_bfs_cb(std::vector<Value*> args)
    {
        assert_size(args, 5, "bfs_cb");
        assert_type(args[0], VType::Graph);
        assert_type(args[1], VType::Integer);
        assert_type(args[2], VType::Function);
        assert_type(args[3], VType::List);
        assert_type(args[4], VType::String);
        
        auto g = new GraphValue::Graph();
        auto gv = new GraphValue(g);
        auto s = geti(args[1])->data;
        
        auto f = getfn(args[2]);
        auto callargs = getl(args[3]);
        std::string cb = gets(args[4])->data;
        
        g->insertVertex(s);
        graph::BreadthFirstSearch<GraphValue::Graph> bfs(*getg(args[0])->data, s);
        
        auto f1 = [&](int x) -> bool
        {
            callargs->data.push_back(convertToValue(x));
            f->call(callargs->data);
            callargs->data.pop_back();
            return true;
        };
        auto f2 = [&](int x, int y) -> bool
        {
            auto listval = getl(convertToValue(std::vector<int>{x,y}));
            callargs->data.push_back(listval);
            f->call(callargs->data);
            callargs->data.pop_back();
            return true;
        };
        if (cb == "p1")
            bfs.setp1(f1);
        if (cb == "p2")
            bfs.setp2(f1);
        if (cb == "p3")
            bfs.setp3(f2);
        bfs.setp4([&](int x,int y)
        {
            g->insertVertex(y);
            g->insertEdge(x, y, 1);
            if (cb == "p4")
                f2(x, y);
            return true;
        });
        bfs();
        return gv;
    }
    Value* graph_dfs_animate(std::vector<Value*> args)
    {
        assert_arg_list(args, 2, {VType::Graph, VType::Integer}, "dfs_animate");
        auto g = new GraphValue::Graph();
        auto gv = new GraphValue(g);
        auto s = geti(args[1])->data;
        g->insertVertex(s);
        new WindowValue(gv, new TreeLayout(*gv, s));// FIXME: Leak
        graph::DepthFirstSearch<GraphValue::Graph> dfs(*getg(args[0])->data, s);
        dfs.setp4([&](int x,int y)
        {
            g->insertVertex(y);
            g->insertEdge(x, y, 1);
            gv->changeCallback();
            QApplication::processEvents();
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            return true;
        });
        dfs();
        return gv;
    }
    Value* graph_dfs(std::vector<Value*> args)
    {
        assert_arg_list(args, 2, {VType::Graph, VType::Integer}, "dfs");
        auto g = new GraphValue::Graph();
        auto gv = new GraphValue(g);
        auto s = geti(args[1])->data;
        g->insertVertex(s);
        graph::DepthFirstSearch<GraphValue::Graph> dfs(*getg(args[0])->data, s);
        dfs.setp4([&](int x,int y)
        {
            g->insertVertex(y);
            g->insertEdge(x, y, 1);
            return true;
        });
        dfs();
        return gv;
    }
    Value* graph_dfs_cb(std::vector<Value*> args)
    {
        assert_size(args, 5, "dfs_cb");
        assert_type(args[0], VType::Graph);
        assert_type(args[1], VType::Integer);
        assert_type(args[2], VType::Function);
        assert_type(args[3], VType::List);
        assert_type(args[4], VType::String);
        
        auto g = new GraphValue::Graph();
        auto gv = new GraphValue(g);
        auto s = geti(args[1])->data;
        
        auto f = getfn(args[2]);
        auto callargs = getl(args[3]);
        std::string cb = gets(args[4])->data;
        
        g->insertVertex(s);
        graph::DepthFirstSearch<GraphValue::Graph> dfs(*getg(args[0])->data, s);
        
        auto f1 = [&](int x) -> bool
        {
            callargs->data.push_back(convertToValue(x));
            f->call(callargs->data);
            callargs->data.pop_back();
            return true;
        };
        auto f2 = [&](int x, int y) -> bool
        {
            auto listval = getl(convertToValue(std::vector<int>{x,y}));
            callargs->data.push_back(listval);
            f->call(callargs->data);
            callargs->data.pop_back();
            return true;
        };
        if (cb == "p1")
            dfs.setp1(f1);
        if (cb == "p2")
            dfs.setp2(f1);
        if (cb == "p3")
            dfs.setp3(f2);
        dfs.setp4([&](int x,int y)
        {
            g->insertVertex(y);
            g->insertEdge(x, y, 1);
            if (cb == "p4")
                f2(x, y);
            return true;
        });
        dfs();
        return gv;
    }
    Value* graph_kruskal_animate(std::vector<Value*> args)
    {
        assert_arg_list(args, 1, {VType::Graph}, "kruskal_animate");
        auto g = new GraphValue::Graph();
        auto gv = new GraphValue(g);
        new WindowValue(gv, new CircularLayout(*gv));// FIXME: Leak
        auto state = graph::Kruskal(*getg(args[0])->data, [&](int x,int y, int w)
        {
            g->insertVertex(x);
            g->insertVertex(y);
            g->insertEdge(x, y, w);
            gv->changeCallback();
            QApplication::processEvents();
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            return true;
        });
        return gv;
    }
    Value* graph_kruskal(std::vector<Value*> args)
    {
        assert_arg_list(args, 1, {VType::Graph}, "kruskal");
        auto g = new GraphValue::Graph();
        auto gv = new GraphValue(g);
//         new WindowValue(gv, new CircularLayout(*gv));// FIXME: Leak
        auto state = graph::Kruskal(*getg(args[0])->data, [&](int x,int y, int w)
        {
            g->insertVertex(x);
            g->insertVertex(y);
            g->insertEdge(x, y, w);
//             gv->changeCallback();
//             QApplication::processEvents();
//             std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            return true;
        });
        return gv;
    }
    Value* graph_kruskal_cb(std::vector<Value*> args)
    {
        assert_size(args, 3, "kruskal_cb");
        assert_type(args[0], VType::Graph);
        assert_type(args[1], VType::Function);
        assert_type(args[2], VType::List);
        
        auto g = new GraphValue::Graph();
        auto gv = new GraphValue(g);
        auto f = getfn(args[1]);
        auto callargs = getl(args[2]);
//         new WindowValue(gv, new CircularLayout(*gv));// FIXME: Leak
        auto state = graph::Kruskal(*getg(args[0])->data, [&](int x,int y, int w)
        {
            g->insertVertex(x);
            g->insertVertex(y);
            g->insertEdge(x, y, w);
            auto listval = getl(convertToValue(std::vector<int>{x,y}));
            callargs->data.push_back(listval);
            f->call(callargs->data);
            callargs->data.pop_back();
            QApplication::processEvents();
            //std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            return true;
        });
        return gv;
    }
    Value* graph_set_graph_attribute(std::vector<Value*> args)
    {
        assert_size(args, 3);
        assert_type(args[0], VType::Graph);
        assert_type(args[1], VType::String);
        
        auto g = getg(args[0]);
        auto s = gets(args[1]); 
        g->getGraphAttribs()->data[s->data] = args[2];
        return g;
    }
    Value* graph_get_graph_attribute(std::vector<Value*> args)
    {
        assert_size(args, 2);
        assert_type(args[0], VType::Graph);
        assert_type(args[1], VType::String);
        auto g = getg(args[0]);
        auto s = gets(args[1]); 
        return g->getGraphAttribs()->data[s->data];
    }
    
    Value* graph_set_vertex_attribute(std::vector<Value*> args)
    {
        assert_size(args, 4);
        assert_type(args[0], VType::Graph);
        assert_type(args[1], VType::String);
        assert_type(args[2], VType::Integer);
        
        
        auto g = getg(args[0]);
        auto s = gets(args[1]); 
        auto v = geti(args[2]);
        
        g->setVertexAttribute(s->data, v->data, args[3]);
        return g;
    }
    Value* graph_set_vertex_attribute_all(std::vector<Value*> args)
    {
        assert_size(args, 3);
        assert_type(args[0], VType::Graph);
        assert_type(args[1], VType::String);
        assert_type(args[2], VType::Vattr);
        
        auto g = getg(args[0]);
        auto s = gets(args[1]); 
        g->setVertexAttribute(s->data, static_cast<VattrValue*>(args[2]));
        return g;
    }
    Value* graph_get_vertex_attribute(std::vector<Value*> args)
    {
        assert_size(args, 3);
        assert_type(args[0], VType::Graph);
        assert_type(args[1], VType::String);
        assert_type(args[2], VType::Integer);
        
        auto g = getg(args[0]);
        auto s = gets(args[1]); 
        auto v = geti(args[2]);
        return g->getVertexAttribute(s->data, v->data);
    }
    
    Value* graph_vertex_list(std::vector<Value*> args)
    {
        assert_arg_list(args, 1, {VType::Graph}, "vertex_list");
        return convertToValue(graph::VertexList(*getg(args[0])->data));
    }
    Value* graph_edge_list(std::vector<Value*> args)
    {
        assert_arg_list(args, 1, {VType::Graph}, "edge_list");
        auto el = graph::EdgeList(*getg(args[0])->data);
        return convertToValue(el);
    }
    Value* graph_sorted_edge_list(std::vector<Value*> args)
    {
        assert_arg_list(args, 1, {VType::Graph}, "sorted_edge_list");
        auto el = graph::sortedEdgeList(*getg(args[0])->data);
        return convertToValue(el);
    }
    Value* graph_degree_map(std::vector<Value*> args)
    {
        assert_arg_list(args, 1, {VType::Graph}, "degree_map");
        return convertToValue(graph::DegreeMap(*getg(args[0])->data));
    }
    
    Value* graph_degree_sequence(std::vector<Value*> args)
    {
        assert_arg_list(args, 1, {VType::Graph}, "degree_sequence");
        return convertToValue(graph::DegreeSequence(*getg(args[0])->data));
    }
    Value* graph_centre(std::vector<Value*> args)
    {
        assert_arg_list(args, 1, {VType::Graph}, "centre");
        return convertToValue(graph::Centre(*getg(args[0])->data));
    }
    
    Value* graph_periphery(std::vector<Value*> args)
    {
        assert_arg_list(args, 1, {VType::Graph}, "periphery");
        return convertToValue(graph::Periphery(*getg(args[0])->data));
    }
    Value* graph_neighbors(std::vector<Value*> args)
    {
        assert_arg_list(args, 2, {VType::Graph, VType::Integer}, "neighbors");
        return convertToValue(graph::OutVertexList(*getg(args[0])->data, geti(args[1])->data));
    }
    
    Value* graph_in_vertex_list(std::vector<Value*> args)
    {
        assert_arg_list(args, 2, {VType::Graph, VType::Integer}, "in_vertex_list");
        return convertToValue(graph::InVertexList(*getg(args[0])->data, geti(args[1])->data));
    }
    
    Value* graph_eulerian_trail(std::vector<Value*> args)
    {
        assert_arg_list(args, 1, {VType::Graph}, "eulerian_trail");
        return convertToValue(graph::EulerianTrail(*getg(args[0])->data));
    }
    
    Value* graph_eulerian_circuit(std::vector<Value*> args)
    {
        assert_arg_list(args, 1, {VType::Graph}, "eulerian_circuit");
        assert_type(args[0], VType::Graph);
        return convertToValue(graph::EulerianCircuit(*getg(args[0])->data));
    }
    
    Value* graph_hamiltonian_path(std::vector<Value*> args)
    {
        assert_arg_list(args, 1, {VType::Graph}, "hamiltonian_path");
        return convertToValue(graph::HamiltonianPath(*getg(args[0])->data));
    }
    
    Value* graph_hamiltonian_cycle(std::vector<Value*> args)
    {
        assert_arg_list(args, 1, {VType::Graph}, "hamiltonian_cycle");
        return convertToValue(graph::HamiltonianCycle(*getg(args[0])->data));
    }
    
    Value* graph_vertex_coloring(std::vector<Value*> args)
    {
        assert_arg_list(args, 1, {VType::Graph}, "vertex_coloring");
        auto state = graph::WelshPowellColoring(*getg(args[0])->data);
        std::vector<Value*> v = {convertToValue(state.getColorMap()), convertToValue(state.noOfColorsUsed())}; 
        return convertToValue(v);
    }
    
    Value* graph_dijkstra_path(std::vector<Value*> args)
    {
        assert_arg_list(args, 3, {VType::Graph, VType::Integer, VType::Integer}, "dijkstra_path");
        
        auto g = getg(args[0]);
        auto x = geti(args[1]);
        auto y = geti(args[2]);
        
        auto&& result = graph::DijkstraPath(*g->data, x->data);
        return convertToValue(result[y->data]);
    }
}
