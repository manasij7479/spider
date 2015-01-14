#ifndef SPIDER_LAYOUT_BIPARTITELAYOUT_HPP
#define SPIDER_LAYOUT_BIPARTITELAYOUT_HPP
#include "Layout/Layout.hpp"
#include "graph/algorithm/collections.hpp"
namespace spider
{
    template<typename Graph>
    class BipartiteLayout : public Layout<Graph>
    {
        typedef Layout<Graph> Base;
    public:
        BipartiteLayout(Graph& g, float fraction_=0.5, bool isVertical_=true):
        Layout<Graph>(g),fraction(fraction_),isVertical(isVertical_)
        {
            Base::hasEdgeData = false;
        };
        
        virtual void generate(Rect bounds)
        {
            int order = Base::g.order();
            float xp,yp,inc;
            auto vlist = graph::VertexList(Base::g);
            
            int start=0, end=order*fraction;
            for(int i=0;i<2;++i)
            {
                if(isVertical == true)
                {
                    xp = (bounds.max.x+bounds.min.x)/4 + (bounds.max.x+bounds.min.x)/2*i;
                    yp = bounds.min.y; 
                    inc = (bounds.max.y+bounds.min.y)/(end-start);
                }
                else
                {
                    xp = bounds.min.x;
                    yp = (bounds.max.y+bounds.min.y)/4 + (bounds.max.x+bounds.min.x)/2*i;
                    inc = (bounds.max.x+bounds.min.x)/(end-start);
                }
                for(int j=start;j<end;++j)
                {
                    Base::points.value(vlist[j])=Point({xp,yp});
                    if(isVertical == true)
                        yp += inc;
                    else
                        xp += inc;
                }
                start = end;
                end = order;
            }
        }
    private:
        float fraction;
        bool isVertical;
    };
}
#endif
