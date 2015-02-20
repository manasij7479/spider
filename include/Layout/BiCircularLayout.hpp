/**
 * \brief BiCircularLayout.hpp - Header file that contains functions to generate
 * BiCircular Layout for drawing a graph. The layout has two concentric circles
 * on whose circumference the vertex are plotted at equal intervals.
 * **/
 #ifndef SPIDER_LAYOUT_BICIRCULARLAYOUT_HPP
#define SPIDER_LAYOUT_BICIRCULARLAYOUT_HPP
#include "Layout/Layout.hpp"
#include "graph/algorithm/collections.hpp"
namespace spider
{
    template<typename Graph>
    class BiCircularLayout : public Layout<Graph>
    {
        typedef Layout<Graph> Base;
    public:
        BiCircularLayout(Graph& g,float inner_count_fraction_=0.5,float in_rad_fraction_=0.5):
        Layout<Graph>(g),inner_count_fraction(inner_count_fraction_),in_rad_fraction(in_rad_fraction_)
        {
            Base::hasEdgeData = false;
        };
        
        /**
         * \brief - generates x and y coordinates of each vertex
         * 
         * Rect bounds - Parameter, contains the x and y coordinates of 
         * the boundary of the drawing area
         * **/
        virtual void generate(Rect bounds)
        {
            Point center = {(bounds.max.x+bounds.min.x)/2, (bounds.max.y+bounds.min.y)/2};
            float xspan = center.x - bounds.min.x;
            float yspan = center.y - bounds.min.y;
            float outradius = std::min(xspan,yspan);
            float inradius = outradius*in_rad_fraction;
            int inner = Base::g.order() * inner_count_fraction;
            int outer = Base::g.order() - inner;
            float inc = 2*3.142/inner;
            float deg = 0;
            auto vlist = graph::VertexList(Base::g);
            for(int i=0;i<inner;++i)
            {
                float xp= center.x+inradius*cos(deg);
                float yp= center.y+inradius*sin(deg);
                deg+=inc;
                Base::points.value(vlist[i])=Point({xp,yp});
            }
            deg = 0;
            inc = 2*3.142/outer;
            for(uint i=inner ;i<Base::g.order();++i)
            {
                float xp= center.x+outradius*cos(deg);
                float yp= center.y+outradius*sin(deg);
                deg+=inc;
                Base::points.value(vlist[i])=Point({xp,yp});
            }
            
        }
    private:
        float inner_count_fraction,in_rad_fraction;
    };
}
#endif
