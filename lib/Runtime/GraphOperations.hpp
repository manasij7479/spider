#include "graph/graph.hpp"
#include "graph/util/generate.hpp"
#include "NewRuntime/Type.hpp"
#include "NewRuntime/GraphValue.hpp"
namespace spider
{
    Value* insert_vertex(std::vector<Value*> args)
    {
        assert_size(args, 2);
        assert_type(args[0], VType::Graph);
        assert_type(args[1], VType::String);
        auto g = static_cast<GraphValue*>(args[0]);
        auto v = static_cast<StringValue*>(args[1]);
        g->data->insertVertex(v->data);
        return g;
    }
    Value* order(std::vector<Value*> args)
    {
        assert_size(args, 1);
        assert_type(args[0], VType::Graph);
        return new IntegerValue(static_cast<GraphValue*>(args[0])->data->order());
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
    Value* std_graph(std::vector<Value*> args)
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
    
    
}