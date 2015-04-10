 #ifndef SPIDER_LAYOUT_GRIDLAYOUT_HPP
#define SPIDER_LAYOUT_GRIDLAYOUT_HPP
#include "Layout/Layout.hpp"
#include "graph/algorithm/collections.hpp"
/**
 * \brief GridLayout.hpp - Header file that contains functions to generate Grid Layout.
 * 
 * Grid Layout for drawing a graph - The layout plots the vertices at equal distance
 * from all adjacent vertices to form a grid.
 * **/
namespace spider
{
    /**
     * \brief - Grid Layout for drawing a graph. The layout plots the vertices at equal distance
     * from all adjacent vertices to form a grid. This layout is especially useful in plotting graphs such as
     * Grid Graph etc.
     * **/
    class GridLayout : public Layout
    {
    public:
       /**
         * \brief - Constructor
         * 
         * @param GraphValue& g - First Parameter, a graph object and attributes
         * 
         * @param int n_ - Second Parameter, the number of rows or columns. 
         * 
         * @param bool iscol_ = true - Third Parameter, to check whether n_ is cloumn or not
         * , default value true
         * **/
       GridLayout(GraphValue& g,int n_,bool iscol_ = true):
        Layout(g),n(n_),iscol(iscol_)
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
            int r,c;
            if(iscol)
            {
                r = n;
                c = getGraph().order()/r;
            }
            else
            {
                c = n;
                r = getGraph().order()/c;
            }
            float incx = (bounds.max.x - bounds.min.x)/(r-1);
            float incy = (bounds.max.y - bounds.min.y)/(c-1);
            
            auto&& vlist = graph::VertexList(getGraph());
            for (uint i=0; i < vlist.size(); ++i)
            {
                int x = i%r;
                int y = i/r;
                points.value(vlist[i])=Point({bounds.min.x+x*incx,bounds.min.y+y*incy});
            }
            
        }
    private:
        int n;
        bool iscol;
    };
}
#endif
