#ifndef SPIDER_FORCE_BASED_LAYOUT_HPP
#define SPIDER_FORCE_BASED_LAYOUT_HPP
#include "Layout/Layout.hpp"
#include "Layout/RandomLayout.hpp"
#include "graph/algorithm/predicates.hpp"
#include "graph/algorithm/collections.hpp"
#include <iostream>
namespace spider
{
    template <typename Graph>
    class ForceBasedLayout : public Layout<Graph>
    {
        typedef Layout<Graph> Base;
    public:
        ForceBasedLayout(Graph& g, float gc_ = 3000, float kc_ = 1.0/1000, float errf_ = 0.1)
        :Base(g), gc(gc_), kc(kc_), errf(errf_){};
        void generate(Rect bounds, graph::VertexAttribute<Graph,Point> basis)
        {
            auto& va = basis;
            int iter = 10000;
            while(iter--)
            {
                graph::VertexAttribute<Graph,Point> newva;
                int numeq = 0; // number of vertices in equilibrium 
                Point old;
                for(auto x=Base::g.begin();x!=Base::g.end();++x)
                {
                    Point cur=va.value(x->first);
                    old = cur;
                    float fx=0;
                    float fy=0;
                    for(auto y=Base::g.begin();y!=Base::g.end();++y)
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
                            if(graph::isAdjacent(Base::g,x->first,y->first))
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
                if (numeq == Base::g.order()) // Can be decreased
                {
//                     std::cout<<"EQ "<<iter<<std::endl;
                    break;
                }
            }
            Base::setVertexAttribute(va);
        }
        void generate(Rect bounds)
        {
            RandomLayout<Graph> rl(Base::g);
            rl.generate(bounds);
            generate(bounds, rl.getVertexAttribute());
            
        }
    private:
        float gc;
        float kc;
        float errf;
    };
}
#endif