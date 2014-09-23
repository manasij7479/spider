#ifndef SPIDER_LAYOUT_HPP
#define SPIDER_LAYOUT_HPP
#include "graph/structures/attribute.hpp"
#include "Layout/Geometry.hpp"
#include <random>
namespace spider
{
    template <typename Graph>
    class Layout
    {
        typedef typename Graph::VertexType V;
        typedef graph::VertexAttribute<Graph,Point> VA;
        typedef graph::EdgeAttribute<Graph,Curve> EA;
        
    public:
        Layout(Graph& g_):g(g_){};
        
        virtual void generate(Rect bounds){}
        Point getVertex(V v)
        {
            return points.value(v);
        }
        Curve getEdge(V x, V y)
        {
            if (!hasEdgeData)
                return {getVertex(x),getVertex(y)};
            else return curves.value(x,y);
        }
        Graph& getGraph(){return g;}
        VA getVertexAttribute(){return points;}
        EA getEdgeAttribute(){return curves;}
        void setVertexAttribute(VA va){points=va;}
        void setEdgeAttribute(EA ea){curves = ea;}
    protected:
        graph::VertexAttribute<Graph,Point> points;
        graph::EdgeAttribute<Graph,Curve> curves;
        bool hasEdgeData;
        Graph& g;
    };
}
#endif