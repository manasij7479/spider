/**
 * \brief LinearLayout.hpp - Header file that contains functions to generate
 * Linear Layout for drawing a graph. The layout plots the vertices along a straight
 * line at equal distance.
 * **/
#ifndef SPIDER_LAYOUT_LINEARLAYOUT_HPP
#define SPIDER_LAYOUT_LINEARLAYOUT_HPP
#include "Layout/Layout.hpp"
#include "graph/algorithm/collections.hpp"
namespace spider
{
    template<typename Graph>
    class LinearLayout : public Layout<Graph>
    {
        typedef Layout<Graph> Base;
    public:
        LinearLayout(Graph& g, bool isVertical_ = false):
        Layout<Graph>(g),isVertical(isVertical_)
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
            int order = Base::g.order();
            float xp,yp,inc;
            if(isVertical == true)
            {
                xp = (bounds.max.x+bounds.min.x)/2;
                yp = bounds.min.y; 
                inc = (bounds.max.y+bounds.min.y)/order-1;
            }
            else
            {
                xp = bounds.min.x;
                yp = (bounds.max.y+bounds.min.y)/2;
                inc = (bounds.max.x+bounds.min.x)/order-1;
            }
            
            auto vlist = graph::VertexList(Base::g);
            for(int i=0;i<order;++i)
            {
                Base::points.value(vlist[i])=Point({xp,yp});
                if(isVertical == true)
                    yp += inc;
                else
                    xp += inc;
            }
        }
    private:
        int n;
        bool isVertical;
    };
}
#endif
