#ifndef SPIDER_RANDOM_LAYOUT_HPP
#define SPIDER_RANDOM_LAYOUT_HPP
#include "Layout/Layout.hpp"
#include <iostream>
namespace spider
{
    template <typename Graph>
    class RandomLayout : public Layout<Graph>
    {
        typedef Layout<Graph> Base;
    public:
        RandomLayout(Graph& g, float m = 1.5f):
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
//             std::uniform_real_distribution<> x(bounds.min.x, bounds.max.x),y(bounds.min.y, bounds.max.y);  

            for(auto it=Base::g.begin();it!=Base::g.end();++it)
            {
                float xp,yp;
                do {
                    xp=x(twister);
                    yp=y(twister);
                }while (!Within(bounds,{xp,yp}));
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