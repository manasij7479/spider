#ifndef SPIDER_LAYOUT_TREELAYOUT_HPP
#define SPIDER_LAYOUT_TREELAYOUT_HPP
#include<algorithm>
#include "Layout/Layout.hpp"
#include "graph/algorithm/collections.hpp"
#include "graph/algorithm/enumeration.hpp"
namespace spider
{
    template <typename Graph>
    bool sortComparison(std::vector<typename Graph::VertexType> i, std::vector<typename Graph::VertexType> j) { return (i.size()<j.size()); }
    
    template<typename Graph>
    class TreeLayout : public Layout<Graph>
    {
        typedef Layout<Graph> Base;
    public:
        TreeLayout(Graph& g, typename Graph::VertexType v_):
        Layout<Graph>(g),v(v_)
        {
            Base::hasEdgeData = false;
        };
        
        virtual void generate(Rect bounds)
        {
            graph::BreadthFirstSearch<Graph> bfs(Base::g,v);
            bfs();
            auto parentarray = bfs.getParentArray();
            std::vector<std::vector<typename Graph::VertexType>> patharray;
            for(auto x=Base::g.begin();x!=Base::g.end();++x)
                if(x->first != v)
                    patharray.push_back(parentarray.getPath(x->first));
            std::stable_sort(patharray.begin(),patharray.end(),sortComparison<Graph>);
//             for(int i=0;i<patharray.size();++i)
//                 std::cout<<i<<" "<<patharray[i].back()<<std::endl;
            int ecentricity = patharray.back().size()-1;
            float yinc = (bounds.max.y-bounds.min.y)/ecentricity;
            float yp = bounds.min.y+yinc;
            
            int nadded = 0;
            Base::points.value(v)=Point({(bounds.max.x+bounds.min.x)/2,bounds.min.y});
            for(int layer=1;layer<=ecentricity;++layer)
            {
                int layerend;
                for(int i=nadded;i<patharray.size();++i)
                {
                    if(patharray[i].size()!=layer+1)
                    {
                        layerend = i;
                        break;
                    }
                    if(i==patharray.size()-1)
                    {
                        layerend=i+1;
                        break;
                    }
                }
                
                float xinc = (bounds.max.x-bounds.min.x)/(layerend-nadded-1);
                float xp = bounds.min.x;
                for(int i=nadded;i<layerend;++i)
                {
//                     std::cout<<i<<" "<<patharray[i].back()<<std::endl;
                    Base::points.value(patharray[i].back())=Point({xp,yp});
                    xp += xinc;
                }
                
                nadded = layerend;
                yp += yinc;
            }
        }
        /*virtual void generate(Rect bounds)
        {
            Point center = {(bounds.max.x+bounds.min.x)/2, (bounds.max.y+bounds.min.y)/2};
            float xspan = center.x - bounds.min.x;
            float yspan = center.y - bounds.min.y;
            float outradius = std::min(xspan,yspan);
            float inradius = outradius*in_rad_fraction;
            int inner = Base::g.order() * inner_count_fraction;
            int outer = Base::g.order() - inner;
            float inc = 2*3.142/inner;
            float deg = 0;
            auto vlist = graph::VertexList(Base::g);
            for(int i=0;i<inner;++i)
            {
                float xp= center.x+inradius*cos(deg);
                float yp= center.y+inradius*sin(deg);
                deg+=inc;
                Base::points.value(vlist[i])=Point({xp,yp});
            }
            deg = 0;
            inc = 2*3.142/outer;
            for(int i=inner ;i<Base::g.order();++i)
            {
                float xp= center.x+outradius*cos(deg);
                float yp= center.y+outradius*sin(deg);
                deg+=inc;
                Base::points.value(vlist[i])=Point({xp,yp});
            }
            
        }*/
    private:
        typename Graph::VertexType v;
    };
}
#endif
