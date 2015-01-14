#ifndef SPIDER_RUNTIME_GRAPH_VALUE_HPP
#define SPIDER_RUNTIME_GRAPH_VALUE_HPP
#include "graph/graph.hpp"
#include "graph/util/io.hpp"
#include "Runtime/Type.hpp"
namespace spider
{
    class GraphValue : public Value
    {
    public:
        typedef graph::AdjacencyList<std::string, int> Graph;
        GraphValue(Graph* g)
            :data(g), Value(VType::Graph){};
        GraphValue(bool dir = false)
            :data(new Graph(dir)), Value(VType::Graph){};
        std::string show()
        {
            std::ostringstream out;
            graph::displayGraph(*data, out);
            return out.str();
        }
        Graph* data;
        
        void setCallback(std::function<void(void)> f){changeCallbacks.push_back(f);}
        void changeCallback(){for(auto&& f: changeCallbacks)f();}
    private:
        std::vector<std::function<void(void)>> changeCallbacks;
    };
    
}
#endif