#include "graph/graph.hpp"
#include "graph/util/generate.hpp"
#include "graph/algorithm/operations.hpp"
#include "Runtime/Type.hpp"
#include "Runtime/GraphValue.hpp"
namespace spider
{
    GraphValue* getg(Value* v)
    {
        return static_cast<GraphValue*>(v);
    }
    Value* graph_insert_vertex(std::vector<Value*> args)
    {
        assert_size(args, 2);
        assert_type(args[0], VType::Graph);
        assert_type(args[1], VType::String);
        auto g = getg(args[0]);
        auto v = static_cast<StringValue*>(args[1]);
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
        auto v = static_cast<StringValue*>(args[1]);
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
        auto x = static_cast<StringValue*>(args[1]);
        auto y = static_cast<StringValue*>(args[2]);
        
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
    std::map<std::string, F> GraphNameMap = 
    {
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
        {"wagner", graph::gen::wagner},
        {"butterfly", graph::gen::butterfly},
        {"petersen", graph::gen::petersen},
        {"durer", graph::gen::durer},
        {"desargues", graph::gen::desargues},
        {"mobius_kantor", graph::gen::mobius_kantor},
        {"dodecahedron", graph::gen::dodecahedron},
        {"nauru", graph::gen::nauru}
    };
    Value* graph_generate(std::vector<Value*> args)
    {
        assert_size(args, greater_eq(1));
        assert_type(args[0], VType::String);
        std::vector<int> newArgs;
        for(int i = 1; i < args.size(); ++i)
        {
            assert_type(args[i], VType::Integer);
            newArgs.push_back(static_cast<IntegerValue*>(args[i])->data);
        }
        auto g  = new GraphValue::Graph(
            GraphNameMap[static_cast<StringValue*>(args[0])->data](newArgs, 1));
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
    
    Value* graph_edgedeletionsubgraph(std::vector<Value*> args)
    {
        assert_size(args, 3);
        assert_type(args[0], VType::Graph);
        assert_type(args[1], VType::String);
        assert_type(args[2], VType::String);
        
        auto x = static_cast<StringValue*>(args[1]);
        auto y = static_cast<StringValue*>(args[2]);
        
        auto g = new GraphValue::Graph(graph::EdgeDeletionSubgraph(*(getg(args[0])->data), x->data, y->data));
        return new GraphValue(g);
    }
    
    Value* graph_vertexdeletionsubgraph(std::vector<Value*> args)
    {
        assert_size(args, 2);
        assert_type(args[0], VType::Graph);
        assert_type(args[1], VType::String);
        
        auto x = static_cast<StringValue*>(args[1]);
        
        auto g = new GraphValue::Graph(graph::VertexDeletionSubgraph(*(getg(args[0])->data), x->data));
        return new GraphValue(g);
    }
    
    Value* graph_edgecontractionminor(std::vector<Value*> args)
    {
        assert_size(args, 3);
        assert_type(args[0], VType::Graph);
        assert_type(args[1], VType::String);
        assert_type(args[2], VType::String);
        
        auto x = static_cast<StringValue*>(args[1]);
        auto y = static_cast<StringValue*>(args[2]);
        
        auto g = new GraphValue::Graph(graph::EdgeContractionMinor(*(getg(args[0])->data), x->data, y->data));
        return new GraphValue(g);
    }
}