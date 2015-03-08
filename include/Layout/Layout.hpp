/**
 * \brief Layout.hpp - Header file that contains the attributes of layout of a graph
 * **/

#ifndef SPIDER_LAYOUT_HPP
#define SPIDER_LAYOUT_HPP
#include "graph/structures/attribute.hpp"
#include "Layout/Geometry.hpp"
#include <random>
#include "Runtime/GraphValue.hpp"
namespace spider
{
    class Layout
    {
        typedef typename GraphValue::Graph::VertexType V;
        typedef graph::VertexAttribute<GraphValue::Graph,Point> VA;
        typedef graph::EdgeAttribute<GraphValue::Graph,Curve> EA;
        
    public:
        Layout(GraphValue& g_):g(g_){};
        virtual ~Layout(){}
        virtual void generate(Rect){}
        /**
         * \brief - Returns attributes of vertex
         * 
         * V v- Parameter, a vertex
        **/
        Point getVertex(V v)
        {
            return points.value(v);
        }
        /**
         * \brief - Returns the attributes of an edge between the vertex x and vetex y
         * 
         * V x - First parameter, a vertex
         * 
         * V y - Second parameter, a vertex        
        **/
        Curve getEdge(V x, V y)
        {
            if (!hasEdgeData)
                return {getVertex(x),getVertex(y)};
            else return curves.value(x,y);
        }
        /** \brief - returns a graph g **/
        GraphValue::Graph& getGraph(){return *(g.data);}
        /** \brief - returns attribute of a Vertex **/
        VA getVertexAttribute(){return points;}
        /** \brief - returns attribute of an edge **/
        EA getEdgeAttribute(){return curves;}
        /** \brief - assigns attributes of a vertex to points
         * 
         * Va va - Parameter, attrbiute of a vertex
         * **/
        void setVertexAttribute(VA va){points=va;}
        /** \brief - assigns attributes of an edge to curves
         * 
         * EA ea - Parameter, attrbiute of an edge
         * **/
        void setEdgeAttribute(EA ea){curves = ea;}
    protected:
        graph::VertexAttribute<GraphValue::Graph ,Point> points;
        graph::EdgeAttribute<GraphValue::Graph ,Curve> curves;
        bool hasEdgeData;
        GraphValue& g;
    };
}
#endif
