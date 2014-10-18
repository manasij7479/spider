#ifndef SPIDER_CIRCULAR_LAYOUT_HPP
#define SPIDER_CIRCULAR_LAYOUT_HPP
#include "Layout/Layout.hpp"
#include <cmath>
#include <iostream>
namespace spider
{
    template <typename Graph>
    class CircularLayout : public Layout<Graph>
    {
        typedef Layout<Graph> Base;
    public:
        CircularLayout(Graph& g):
            Layout<Graph>(g)
            {
                Base::hasEdgeData = false;
            };
        virtual void generate(Rect bounds)
        {
            Point center = {(bounds.max.x+bounds.min.x)/2, (bounds.max.y+bounds.min.y)/2};
            float xspan = center.x - bounds.min.x;
            float yspan = center.y - bounds.min.y;
            float radius = std::min(xspan,yspan);
            float inc = 2*3.142/Base::g.order();
            float deg = 0;
            for(auto it=Base::g.begin();it!=Base::g.end();++it)
            {
                float xp= center.x+radius*cos(deg);
                float yp= center.y+radius*sin(deg);
                deg+=inc;
                Base::points.value(it->first)=Point({xp,yp});
            }

            
        }        
    };
}
#endif