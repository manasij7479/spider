/**
 * \brief CircularLayout.hpp - Header file that contains functions to generate Circular Layout.
 * 
 * Circular Layout for drawing a graph - The layout has a circle
 * on whose circumference the vertex are plotted at equal intervals.
 * **/
#ifndef SPIDER_CIRCULAR_LAYOUT_HPP
#define SPIDER_CIRCULAR_LAYOUT_HPP
#include "Layout/Layout.hpp"
#include <cmath>
#include <iostream>
namespace spider
{
    class CircularLayout : public Layout
    {
    public:
        CircularLayout(GraphValue& g):
            Layout(g)
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
            float radius = std::min(xspan,yspan);
            float inc = 2*3.142/getGraph().order();
            float deg = 0;
            for(auto it=getGraph().begin();it!=getGraph().end();++it)
            {
                float xp= center.x+radius*cos(deg);
                float yp= center.y+radius*sin(deg);
                deg+=inc;
                points.value(it->first)=Point({xp,yp});
            }

            
        }        
    };
}
#endif
