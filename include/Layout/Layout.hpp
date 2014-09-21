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
            else return curves.value({x,y});
        }
    protected:
        graph::VertexAttribute<Graph,Point> points;
        graph::EdgeAttribute<Graph,Curve> curves;
        bool hasEdgeData;
        Graph& g;
    };
    
    template <typename Graph>
    class RandomLayout : public Layout<Graph>
    {
        typedef Layout<Graph> Base;
    public:
        RandomLayout(Graph& g, float m):
            Layout<Graph>(g),
            twister(rd()),
            modifier(m)
            {
                Base::hasEdgeData = false;
            };
        virtual void generate(Rect bounds)
        {
            Point center = {(bounds.max.x+bounds.min.x)/2, (bounds.max.y+bounds.min.y)/2};
            
            float xspan = center.x - bounds.min.x;
            float yspan = center.y - bounds.min.y;
            
            Point stddev={xspan/modifier,yspan/modifier};
            
            std::normal_distribution<> x(center.x, stddev.x),y(center.y, stddev.y);
            
            for(auto it=Base::g.begin();it!=Base::g.end();++it)
            {
                float xp=x(twister);
                float yp=y(twister);
                Base::points.value(it->first)=Point({xp,yp});
            }

            
        }
    private:
        std::random_device rd;
        std::mt19937 twister;
        float modifier; //Increasing this means the points will be spread out , but also increases the chances of lying out of bounds
        
    };
}
#endif