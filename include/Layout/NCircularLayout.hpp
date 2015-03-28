#ifndef SPIDER_LAYOUT_NCIRCULARLAYOUT_HPP
#define SPIDER_LAYOUT_NCIRCULARLAYOUT_HPP
#include "Layout/Layout.hpp"
#include "graph/algorithm/collections.hpp"
/**
 * \brief NCircularLayout.hpp - Header file that contains functions to generate NCircular Layout.
 * **/
namespace spider
{
    /**
     * \brief -  NCircular Layout for drawing a graph - The layout has N number of concentric circles
     * on whose circumference the vertices are plotted at equal intervals. This layout is especially useful
     * in plotting union of cycle graphs, Hypercube graph etc.
     * **/
    class NCircularLayout : public Layout
    {
    public:
        /**
         * \brief - Constructor
         * 
         * @param GraphValue& g - First Parameter, a graph object and attributes
         * 
         * @param int n_ - Second Parameter, the number of circles. 
         * **/
        NCircularLayout(GraphValue& g, int n_):
        Layout(g),n(n_)
        {
            hasEdgeData = false;
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
            int vcount = getGraph().order()/n;
            int start = 0, end;
            float rinc = std::min(xspan,yspan)/n;
            float radius = rinc;
            
            auto vlist = graph::VertexList(getGraph());
            for(int i=1;i<=n;++i)
            {
                float deg = 0;
                end = (i==n) ? getGraph().order():start+vcount;
                float deginc = 2*3.142/(end-start);
                for(int j=start;j<end;++j)
                {
                    float xp = center.x+radius*cos(deg);
                    float yp = center.y+radius*sin(deg);
                    deg += deginc;
                    points.value(vlist[j]) = Point({xp,yp});
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
