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
        RandomLayout(Graph& g,Point mean={0,0},Point stddev={0.5f,.5f}):
            Layout<Graph>(g),
            twister(rd()),
            x(mean.x,stddev.x),
            y(mean.y,stddev.y)
            {
                Base::hasEdgeData = false;
            };
        virtual void generate(Rect bounds) // FIXME: Ignores bounds
        {
            for(auto it=Base::g.begin();it!=Base::g.end();++it)
            {
                float xp=x(twister);
                float yp=y(twister);
                Base::points.value(it->first)=Point({xp,yp});
                //TODO: transform x,y such that the fall within bounds
            }
        }
    private:
        std::random_device rd;
        std::mt19937 twister;
        std::normal_distribution<> x,y;
        
    };
}
#endif