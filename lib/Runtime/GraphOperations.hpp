#include "graph/graph.hpp"
#include "graph/util/generate.hpp"
#include "graph/algorithm/operations.hpp"
#include "Runtime/Type.hpp"
#include "Runtime/GraphValue.hpp"
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
            newArgs.push_back(geti(args[i])->data);
        }
        auto g  = new GraphValue::Graph(
            GraphNameMap[gets(args[0])->data](newArgs, 1));
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
                
        auto g = new IntegerValue::Graph(graph::Size(*(getg(args[0])->data)));
        return new IntegerValue(g);
    }
    
    Value* graph_out_degree(std::vector<Value*> args)
    {
        assert_size(args, 2);
        assert_type(args[0], VType::Graph);
        assert_type(args[1], VType::String);
        
        auto x = gets(args[1]);
                
        auto g = new IntegerValue::Graph(graph::outDegree(*(getg(args[0])->data), x->data));
        return new IntegerValue(g);
    }
    
    Value* graph_in_degree(std::vector<Value*> args)
    {
        assert_size(args, 2);
        assert_type(args[0], VType::Graph);
        assert_type(args[1], VType::String);
        
        auto x = gets(args[1]);
                
        auto g = new IntegerValue::Graph(graph::inDegree(*(getg(args[0])->data), x->data));
        return new IntegerValue(g);
    }
    
    Value* graph_degree(std::vector<Value*> args)
    {
        assert_size(args, 2);
        assert_type(args[0], VType::Graph);
        assert_type(args[1], VType::String);
        
        auto x = gets(args[1]);
                
        auto g = new IntegerValue::Graph(graph::degree(*(getg(args[0])->data), x->data));
        return new IntegerValue(g);
    }
    
    Value* graph_nregular(std::vector<Value*> args)
    {
        assert_size(args, 1);
        assert_type(args[0], VType::Graph);
                
        auto g = new IntegerValue::Graph(graph::nregular(*(getg(args[0])->data)));
        return new IntegerValue(g);
    }
    
    Value* graph_radius(std::vector<Value*> args)
    {
        assert_size(args, 1);
        assert_type(args[0], VType::Graph);
                
        auto g = new IntegerValue::Graph(graph::Radius(*(getg(args[0])->data)));
        return new IntegerValue(g);
    }
    
    Value* graph_diameter(std::vector<Value*> args)
    {
        assert_size(args, 1);
        assert_type(args[0], VType::Graph);
                
        auto g = new IntegerValue::Graph(graph::Radius(*(getg(args[0])->data)));
        return new IntegerValue(g);
    }
    
    Value* graph_density(std::vector<Value*> args)
    {
        assert_size(args, 1);
        assert_type(args[0], VType::Graph);
                
        auto g = new FloatValue::Graph(graph::Density(*(getg(args[0])->data)));
        return new FloatValue(g);
    }
    
    Value* graph_isVertex(std::vector<Value*> args)
    {
        assert_size(args, 2);
        assert_type(args[0], VType::Graph);
        assert_type(args[1], VType::String);
        return new BoolValue::Graph(graph::isVertex(*(getg(args[0])->data), *(gets(args[1])->data)));
	}
		
    Value* graph_isAdjacent(std::vector<Value*> args)
    {
        assert_size(args, 3);
        assert_type(args[0], VType::Graph);
        assert_type(args[1], VType::String);
        assert_type(args[2], VType::String);
        return new BoolValue::Graph(graph::isAdjacent(*(getg(args[0])->data), *(gets(args[1])->data), *(gets(args[2])->data)));
	}
	
	Value* graph_isSubgraph(std::vector<Value*> args)
    {
        assert_size(args, 2);
        assert_type(args[0], VType::Graph);
        assert_type(args[1], VType::Graph);
        return new BoolValue::Graph(graph::isSubgraph(*(getg(args[0])->data), *(getg(args[1])->data)));
	}
	
	Value* graph_isSpanningSubgraph(std::vector<Value*> args)
    {
        assert_size(args, 2);
        assert_type(args[0], VType::Graph);
        assert_type(args[1], VType::Graph);
        return new BoolValue::Graph(graph::isSpanningSubgraph(*(getg(args[0])->data), *(getg(args[1])->data)));
	}
	
	Value* graph_isConnected(std::vector<Value*> args)
    {
        assert_size(args, 1);
        assert_type(args[0], VType::Graph);
        return new BoolValue::Graph(graph::isConnected(*(getg(args[0])->data)));
	}
	
	VValue* graph_isConnected(std::vector<Value*> args)
    {
        assert_size(args, 3);
        assert_type(args[0], VType::Graph);
        assert_type(args[1], VType::String);
        assert_type(args[2], VType::String);
        return new BoolValue::Graph(graph::isConnected(*(getg(args[0])->data), *(gets(args[1])->data), *(gets(args[2])->data)));
	}
	
	Value* graph_isComponent(std::vector<Value*> args)
    {
        assert_size(args, 2);
        assert_type(args[0], VType::Graph);
        assert_type(args[1], VType::Graph);
        return new BoolValue::Graph(graph::isComponent(*(getg(args[0])->data), *(getg(args[1])->data)));
	}
	
	Value* graph_isRegular(std::vector<Value*> args)
    {
        assert_size(args, 1);
        assert_type(args[0], VType::Graph);
        return new BoolValue::Graph(graph::isRegular(*(getg(args[0])->data)));
	}
	
	Value* graph_isEulerian(std::vector<Value*> args)
    {
        assert_size(args, 1);
        assert_type(args[0], VType::Graph);
        return new BoolValue::Graph(graph::isEulerian(*(getg(args[0])->data)));
	}
	
	Value* graph_isSemiEulerian(std::vector<Value*> args)
    {
        assert_size(args, 1);
        assert_type(args[0], VType::Graph);
        return new BoolValue::Graph(graph::isSemiEulerian(*(getg(args[0])->data)));
	}
	
	Value* graph_isComplete(std::vector<Value*> args)
    {
        assert_size(args, 1);
        assert_type(args[0], VType::Graph);
        return new BoolValue::Graph(graph::isComplete(*(getg(args[0])->data)));
	}
	
	Value* graph_isCyclic(std::vector<Value*> args)
    {
        assert_size(args, 1);
        assert_type(args[0], VType::Graph);
        return new BoolValue::Graph(graph::isCyclic(*(getg(args[0])->data)));
	}
	
	Value* graph_isEdgeless(std::vector<Value*> args)
    {
        assert_size(args, 1);
        assert_type(args[0], VType::Graph);
        return new BoolValue::Graph(graph::isEdgeless(*(getg(args[0])->data)));
	}
	
	Value* graph_isComplement(std::vector<Value*> args)
    {
        assert_size(args, 2);
        assert_type(args[0], VType::Graph);
        assert_type(args[1], VType::Graph);
        return new BoolValue::Graph(graph::isComplement(*(getg(args[0])->data), *(getg(args[1])->data)));
	}
	
	Value* graph_isSparse(std::vector<Value*> args)
    {
        assert_size(args, 1);
        assert_type(args[0], VType::Graph);
        return new BoolValue::Graph(graph::isSparse(*(getg(args[0])->data)));
	}
	
	Value* graph_isTree(std::vector<Value*> args)
    {
        assert_size(args, 1);
        assert_type(args[0], VType::Graph);
        return new BoolValue::Graph(graph::isTree(*(getg(args[0])->data)));
	}
	
	Value* graph_isEmpty(std::vector<Value*> args)
    {
        assert_size(args, 1);
        assert_type(args[0], VType::Graph);
        return new BoolValue::Graph(graph::isEmpty(*(getg(args[0])->data)));
	}
	
	Value* graph_isCentre(std::vector<Value*> args)
    {
        assert_size(args, 2);
        assert_type(args[0], VType::Graph);
        assert_type(args[1], VType::String);
        return new BoolValue::Graph(graph::isCentre(*(getg(args[0])->data), *(gets(args[1])->data)));
	}
	
	Value* graph_isPeriphery(std::vector<Value*> args)
    {
        assert_size(args, 2);
        assert_type(args[0], VType::Graph);
        assert_type(args[1], VType::String);
        return new BoolValue::Graph(graph::isPeriphery(*(getg(args[0])->data), *(gets(args[1])->data)));
	}
}
