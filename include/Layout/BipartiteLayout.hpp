<<<<<<< HEAD
=======
/**
 * \brief BipartiteLayout.hpp - Header file that contains functions to generate Bipartite Layout.
 * 
 * Bipartite Layout for drawing a graph - The layout plots vertices on two sides
 * of an imaginary demarcation such that no two vertices on the same side has an edge
 * between them.
 * **/
>>>>>>> master
#ifndef SPIDER_LAYOUT_BIPARTITELAYOUT_HPP
#define SPIDER_LAYOUT_BIPARTITELAYOUT_HPP
#include "Layout/Layout.hpp"
#include "graph/algorithm/collections.hpp"
/**
 * \brief BipartiteLayout.hpp - Header file that contains functions to generate Bipartite Layout.
 * **/
namespace spider
{
    /**
     * \brief - Bipartite Layout for drawing a graph - The layout plots vertices on two sides
     * of an imaginary demarcation such that no two vertices on the same side has an edge
     * between them. The vertices are plotted at equal distances.
     * This layout is especially useful in plotting graphs such as
     * Complete Bipartite graph etc.
     * **/
    class BipartiteLayout : public Layout
    {
    public:
        /**
         * \brief - Constructor
         * 
         * @param GraphValue& g - First Parameter, a graph object and attributes
         * 
         * @param float fraction_=0.5 - Second Parameter, the fraction of  number of vertices
         * on the right side of the demarcation, default value 0.5
         * 
         * @param bool isVertical_=true - Third Parameter, to check if the vertices will be displayed
         * vertically or horizontally, default value true
         * **/
        BipartiteLayout(GraphValue& g, float fraction_=0.5, bool isVertical_=true):
        Layout(g),fraction(fraction_),isVertical(isVertical_)
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
            auto vlist = graph::VertexList(getGraph());
            
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
                    points.value(vlist[j])=Point({xp,yp});
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
