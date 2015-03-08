/**
 * \brief ForceBasedLayout.hpp - Header file that contains functions to generate
 * Force Based Layout for drawing a graph
 * **/
#ifndef SPIDER_FORCE_BASED_LAYOUT_HPP
#define SPIDER_FORCE_BASED_LAYOUT_HPP
#include "Layout/Layout.hpp"
#include "Layout/RandomLayout.hpp"
#include "graph/algorithm/predicates.hpp"
#include <iostream>
namespace spider
{
    class ForceBasedLayout : public Layout
    {
    public:
        ForceBasedLayout(GraphValue& g, float gc_ = 3000, float kc_ = 1.0/1000, float errf_ = 0.1)
        :Layout(g), gc(gc_), kc(kc_), errf(errf_){};
        /**
         * \brief - generates Vertex Attributes of each vertex
         * 
         * Rect bounds - Parameter, contains the x and y coordinates of 
         * the boundary of the drawing area
         * **/
        void generate(Rect bounds)
        {
            RandomLayout rl(g);
            rl.generate(bounds);
            auto va = rl.getVertexAttribute();
            int iter = 10000;
            while(iter--)
            {
                graph::VertexAttribute<GraphValue::Graph,Point> newva;
                uint numeq = 0; // number of vertices in equilibrium 
                Point old;
                for(auto x=getGraph().begin();x!=getGraph().end();++x)
                {
                    Point cur=va.value(x->first);
                    old = cur;
                    float fx=0;
                    float fy=0;
                    for(auto y=getGraph().begin();y!=getGraph().end();++y)
                    {
                        
                        if(x->first!=y->first)
                        {
                            Point far=va.value(y->first);
                            auto dx=cur.x-far.x;
                            auto dy=cur.y-far.y;
                            auto fgx=gc*(dx/std::fabs(dx))/(dx*dx);
                            auto fgy=gc*(dy/std::fabs(dy))/(dy*dy);
                            fx+=fgx;
                            fy+=fgy;
    //                         std::cout<<fgx<<' '<<fgy<<' ';
                            if(graph::isAdjacent(getGraph(),x->first,y->first))
                            {
    //                             std::cout<<dx <<' '<<dy<<std::endl;

                                float fkx=-kc*dx;
                                float fky=-kc*dy;
                                fx+=fkx;
                                fy+=fky;
    //                             std::cout<<fkx<<' '<<fky<<' ';
                            }
                            
                        }
                        
                    }
    //                 std::cin.get();
    //                 std::cout<<cur.x<<' '<<cur.y<<' '<<fx<<' '<<fy<<std::endl;
                    cur.x+=fx;
                    cur.y+=fy;
                    if (distsquare(cur,old) < errf)
                        numeq++;
                    newva.value(x->first)=cur;
                }
                std::swap(va,newva);
                if (numeq == getGraph().order()) // Can be decreased
                {
//                     std::cout<<"EQ "<<iter<<std::endl;
                    break;
                }
            }
            setVertexAttribute(va);
        }
    private:
        
        float gc;
        float kc;
        float errf;
    };
}
#endif
