#ifndef SPIDER_RUNTIME_GRAPH_VALUE_HPP
#define SPIDER_RUNTIME_GRAPH_VALUE_HPP
#include "graph/graph.hpp"
#include "graph/util/io.hpp"
#include "graph/structures/attribute.hpp"
#include "Runtime/Type.hpp"
#include "Runtime/DictValue.hpp"
#include <QObject>
/**
 * \brief - header files that contains class for GraphValue
 * **/
namespace spider
{
    /**
     * \brief - wrapper class for Graph (graph::AdjacencyList<int,int>)
     * **/
    class GraphValue : public Value
    {
        Q_OBJECT
    public:
        typedef graph::AdjacencyList<int, int> Graph;///<Adjacency AdjacencyList
        /** \brief-constructor**/
        GraphValue(Graph* g)
            :Value(VType::Graph), data(g){attribs = new DictValue;};
	/** \brief-constructor**/
        GraphValue(bool dir = false)
            :Value(VType::Graph), data(new Graph(dir)){attribs = new DictValue;};
	/**
	 * \brief - to display the Adjacency List of a graph.
	 * **/
        std::string show()
        {
            std::ostringstream out;
            graph::displayGraph(*data, out);
            return out.str();
        }
        
        Graph* data;
        /**
	 * \brief - function to set Vertex Attributes.
	 * 
	 * @param std::string attrname - First Parameter, name of attributes
	 * 
	 * @param Graph::VertexType vertex - Second Parameter, a vertex
	 * 
	 * @param Value* value - Third Parameter, a value
	 * **/
        void setVertexAttribute(std::string attrname, Graph::VertexType vertex, Value* value)
        {
            if (vattribs.find(attrname) == vattribs.end())
                vattribs[attrname] = new VattrValue;
            vattribs[attrname]->data[vertex] = value;
        }
        /**
	 * \brief - function to set Vertex Attributes.
	 * 
	 * @param std::string attrname - First Parameter, name of attributes
	 * 
	 * @param Value* value - Second Parameter, a value
	 * **/
        void setVertexAttribute(std::string attrname, VattrValue* value)
        {
            vattribs[attrname] = value;
        }
        /**
	 * \brief - function to get Vertex Attributes.
	 * 
	 * @param std::string attrname - First Parameter, name of attributes
	 * 
	 * @param Graph::VertexType vertex - Second Parameter, a vertex
	 * 
	 * @returns Value* - the value of vertex attributes.
	 * **/
        Value* getVertexAttribute(std::string attrname, Graph::VertexType vertex)
        {
            if (vattribs.find(attrname) == vattribs.end())
                return new VoidValue();
            if (!vattribs[attrname]->isKnown(vertex))
                return new VoidValue();
            return vattribs[attrname]->data[vertex];
        }
        /**
	 * \brief - returns Graph Attributes.
	 * 
	 * @returns DictValue* - attributes of a Graph
	 * **/
        DictValue* getGraphAttribs(){return attribs;}
        /** \brief - funcion to check if an attribute of a vertex is present
	 *
	 * @param std::string attr - Parameter, name of an attribute.
	 **/
        bool hasVertexAttribute(std::string attr) {return vattribs.find(attr) != vattribs.end();}
        /**
	 * \brief - funcion to check if an attribute is present
	 *
	 * @param std::string attr - Parameter, name of an attribute.
	 * **/
        bool hasAttribute(std::string attr) {return attribs->data.find(attr) != attribs->data.end();}
    private:
        DictValue* attribs;
        std::map<std::string, VattrValue*> vattribs;
//         std::map<std::string, graph::EdgeAttribute<Graph, Value*>> eA;
        
    };

    
}
#endif