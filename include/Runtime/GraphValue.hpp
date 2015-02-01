#ifndef SPIDER_RUNTIME_GRAPH_VALUE_HPP
#define SPIDER_RUNTIME_GRAPH_VALUE_HPP
#include "graph/graph.hpp"
#include "graph/util/io.hpp"
#include "Runtime/Type.hpp"
#include <QObject>
namespace spider
{
    class GraphValue : public Value
    {
        Q_OBJECT
    public:
        typedef graph::AdjacencyList<std::string, int> Graph;
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
        
//         void setCallback(std::function<void(void)> f){changeCallbacks.push_back(f);}
        
//     private:
//         std::vector<std::function<void(void)>> changeCallbacks;

    };

    
}
#endif