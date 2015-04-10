<<<<<<< HEAD
=======
/**
 * \brief LinearLayout.hpp - Header file that contains functions to generate Linear Layout.
 * 
 * Linear Layout for drawing a graph - The layout plots the vertices along a straight
 * line at equal distance.
 * **/
>>>>>>> master
#ifndef SPIDER_LAYOUT_LINEARLAYOUT_HPP
#define SPIDER_LAYOUT_LINEARLAYOUT_HPP
#include "Layout/Layout.hpp"
#include "graph/algorithm/collections.hpp"
/**
 * \brief LinearLayout.hpp - Header file that contains functions to generate Linear Layout.
 * **/
namespace spider
{
    /**
     * \brief - Linear Layout for drawing a graph. The layout plots the vertices along a straight
     * line at equal distance. Thios layout is especially useful in plotting graphs such as
     * Path Graphs etc.
    * **/
    class LinearLayout : public Layout
    {
    public:
        /**
         * \brief - Constructor
         * 
         * @param GraphValue& g - First Parameter, a graph object and attributes
         * 
         * @param bool isVertical_ = false_ - Second Parameter, to check if the vertices will be displayed
         * vertically or horizontally, default value true
         * **/
        LinearLayout(GraphValue& g, bool isVertical_ = false):
        Layout(g),isVertical(isVertical_)
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
            int order = getGraph().order();
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
            
            auto vlist = graph::VertexList(getGraph());
            for(int i=0;i<order;++i)
            {
                points.value(vlist[i])=Point({xp,yp});
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
