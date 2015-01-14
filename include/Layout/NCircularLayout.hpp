#ifndef SPIDER_LAYOUT_NCIRCULARLAYOUT_HPP
#define SPIDER_LAYOUT_NCIRCULARLAYOUT_HPP
#include "Layout/Layout.hpp"
#include "graph/algorithm/collections.hpp"
namespace spider
{
    template<typename Graph>
    class NCircularLayout : public Layout<Graph>
    {
        typedef Layout<Graph> Base;
    public:
        NCircularLayout(Graph& g, int n_):
        Layout<Graph>(g),n(n_)
        {
            Base::hasEdgeData = false;
        };
        
        virtual void generate(Rect bounds)
        {
            Point center = {(bounds.max.x+bounds.min.x)/2, (bounds.max.y+bounds.min.y)/2};
            float xspan = center.x - bounds.min.x;
            float yspan = center.y - bounds.min.y;
            int vcount = Base::g.order()/n;
            int start = 0, end;
            float rinc = std::min(xspan,yspan)/n;
            float radius = rinc;
            
            auto vlist = graph::VertexList(Base::g);
            for(int i=1;i<=n;++i)
            {
                float deg = 0;
                end = (i==n) ? Base::g.order():start+vcount;
                float deginc = 2*3.142/(end-start);
                for(int j=start;j<end;++j)
                {
                    float xp = center.x+radius*cos(deg);
                    float yp = center.y+radius*sin(deg);
                    deg += deginc;
                    Base::points.value(vlist[j]) = Point({xp,yp});
                }
                start += vcount;
                radius += rinc;
            }
        }
    private:
        int n;
    };
}
#endif
