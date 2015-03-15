#ifndef SPIDER_RUNTIME_GRAPH_VALUE_HPP
#define SPIDER_RUNTIME_GRAPH_VALUE_HPP
#include "graph/graph.hpp"
#include "graph/util/io.hpp"
#include "graph/structures/attribute.hpp"
#include "Runtime/Type.hpp"
#include "Runtime/DictValue.hpp"
#include <QObject>
namespace spider
{
    class GraphValue : public Value
    {
        Q_OBJECT
    public:
        typedef graph::AdjacencyList<int, int> Graph;
        GraphValue(Graph* g)
            :Value(VType::Graph), data(g){attribs = new DictValue;};
        GraphValue(bool dir = false)
            :Value(VType::Graph), data(new Graph(dir)){attribs = new DictValue;};
        std::string show()
        {
            std::ostringstream out;
            graph::displayGraph(*data, out);
            return out.str();
        }
        
        Graph* data;
        
        void setVertexAttribute(std::string attrname, Graph::VertexType vertex, Value* value)
        {
            if (vattribs.find(attrname) == vattribs.end())
                vattribs[attrname] = new VattrValue;
            vattribs[attrname]->data[vertex] = value;
        }
        void setVertexAttribute(std::string attrname, VattrValue* value)
        {
            vattribs[attrname] = value;
        }
        Value* getVertexAttribute(std::string attrname, Graph::VertexType vertex)
        {
            if (vattribs.find(attrname) == vattribs.end())
                return new VoidValue();
            if (!vattribs[attrname]->isKnown(vertex))
                return new VoidValue();
            return vattribs[attrname]->data[vertex];
        }
        DictValue* getGraphAttribs(){return attribs;}
        bool hasVertexAttribute(std::string attr) {return vattribs.find(attr) != vattribs.end();}
        bool hasAttribute(std::string attr) {return attribs->data.find(attr) != attribs->data.end();}
    private:
        DictValue* attribs;
        std::map<std::string, VattrValue*> vattribs;
//         std::map<std::string, graph::EdgeAttribute<Graph, Value*>> eA;
        
    };

    
}
#endif