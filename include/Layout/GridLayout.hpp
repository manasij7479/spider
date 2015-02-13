/**
 * \brief GridLayout.hpp - Header file that contains functions to generate
 * Grid Layout for drawing a graph. The layout plots the vertices at equal distance
 * from all adjacent vertices to form a grid.
 * **/
 #ifndef SPIDER_LAYOUT_GRIDLAYOUT_HPP
#define SPIDER_LAYOUT_GRIDLAYOUT_HPP
#include "Layout/Layout.hpp"
#include "graph/algorithm/collections.hpp"
namespace spider
{
    template<typename Graph>
    class GridLayout : public Layout<Graph>
    {
        typedef Layout<Graph> Base;
    public:
        GridLayout(Graph& g,int n_,bool iscol_ = true):
        Layout<Graph>(g),n(n_),iscol(iscol_)
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
            int r,c;
            if(iscol)
            {
                r = n;
                c = Base::g.order()/r;
            }
            else
            {
                c = n;
                r = Base::g.order()/c;
            }
            float incx = (bounds.max.x - bounds.min.x)/(r-1);
            float incy = (bounds.max.y - bounds.min.y)/(c-1);
            
            auto&& vlist = graph::VertexList(Base::g);
            for(int i=0;i<vlist.size();++i)
            {
                int x = i%r;
                int y = i/r;
                Base::points.value(vlist[i])=Point({bounds.min.x+x*incx,bounds.min.y+y*incy});
            }
            
        }
    private:
        int n;
        bool iscol;
    };
}
#endif
