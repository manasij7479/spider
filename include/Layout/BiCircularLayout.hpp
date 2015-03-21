/**
 * \brief BiCircularLayout.hpp - Header file that contains functions to generate BiCircular Layout
 * 
 * BiCircular Layout for drawing a graph - The layout has two concentric circles
 * on whose circumference the vertex are plotted at equal intervals.
 * **/
 #ifndef SPIDER_LAYOUT_BICIRCULARLAYOUT_HPP
#define SPIDER_LAYOUT_BICIRCULARLAYOUT_HPP
#include "Layout/Layout.hpp"
#include "graph/algorithm/collections.hpp"
namespace spider
{
    class BiCircularLayout : public Layout
    {
    public:
        BiCircularLayout(GraphValue& g,float inner_count_fraction_=0.5,float in_rad_fraction_=0.5):
        Layout(g),inner_count_fraction(inner_count_fraction_),in_rad_fraction(in_rad_fraction_)
        {
            hasEdgeData = false;
        };
        
        /**
         * \brief - generates x and y coordinates of each vertex
         * 
         * @param Rect bounds - Parameter, contains the x and y coordinates of the boundary of the drawing area
         * **/
        virtual void generate(Rect bounds)
        {
            Point center = {(bounds.max.x+bounds.min.x)/2, (bounds.max.y+bounds.min.y)/2};
            float xspan = center.x - bounds.min.x;
            float yspan = center.y - bounds.min.y;
            float outradius = std::min(xspan,yspan);
            float inradius = outradius*in_rad_fraction;
            int inner = g.data->order() * inner_count_fraction;
            int outer = g.data->order() - inner;
            float inc = 2*3.142/inner;
            float deg = 0;
            auto vlist = graph::VertexList(getGraph());
            for (int i=0;i<inner;++i)
            {
                float xp= center.x+inradius*cos(deg);
                float yp= center.y+inradius*sin(deg);
                deg+=inc;
                points.value(vlist[i])=Point({xp,yp});
            }
            deg = 0;
            inc = 2*3.142/outer;
            for (uint i = inner ; i < getGraph().order() ; ++i)
            {
                float xp= center.x+outradius*cos(deg);
                float yp= center.y+outradius*sin(deg);
                deg+=inc;
                points.value(vlist[i])=Point({xp,yp});
            }
            
        }
    private:
        float inner_count_fraction,in_rad_fraction;
    };
}
#endif
