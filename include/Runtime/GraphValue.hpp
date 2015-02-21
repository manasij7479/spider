#ifndef SPIDER_RUNTIME_GRAPH_VALUE_HPP
#define SPIDER_RUNTIME_GRAPH_VALUE_HPP
#include "graph/graph.hpp"
#include "graph/util/io.hpp"
#include "graph/structures/attribute.hpp"
#include "Runtime/Type.hpp"
#include <map>
#include <QObject>
namespace spider
{
    class GraphValue : public Value
    {
        Q_OBJECT
    public:
        typedef graph::AdjacencyList<int, int> Graph;
        GraphValue(Graph* g)
            :Value(VType::Graph), data(g){};
        GraphValue(bool dir = false)
            :Value(VType::Graph), data(new Graph(dir)){};
        std::string show()
        {
            std::ostringstream out;
            graph::displayGraph(*data, out);
            return out.str();
        }
        
        Graph* data;
        std::map<std::string, graph::GraphAttribute<Graph, Value*>> gA;
        std::map<std::string, graph::VertexAttribute<Graph, Value*>> vA;
        std::map<std::string, graph::EdgeAttribute<Graph, Value*>> eA;
        
    };

    
}
#endif