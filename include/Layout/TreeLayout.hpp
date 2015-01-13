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
            std::sort(patharray.begin(),patharray.end(),sortComparison<Graph>);
            auto elist = graph::EcentricityList(Base::g);
            int ecentricity = elist[v];
            float yinc = (bounds.max.y+bounds.min.y)/ecentricity;
            std::cout<<ecentricity;
            float yp = bounds.min.y+yinc;
            
            int nadded = 0;
            Base::points.value(v)=Point({(bounds.max.x+bounds.min.x)/2,bounds.min.y});
            for(int layer=1;layer<=ecentricity;++layer)
            {
                int layerend;
                for(int i=nadded;i<patharray.size();++i)
                {
                    if(i==patharray.size()-1)
                    {
                        layerend=i+1;
                        break;
                    }
                    if(patharray[i].size()!=layer+1)
                    {
                        layerend = i;
                        break;
                    }
                }
                
                float xinc = (bounds.max.x+bounds.min.x)/(layerend-nadded-1);
                float xp = bounds.min.x;
                for(int i=nadded;i<layerend;++i)
                {
                    Base::points.value(patharray[i].back())=Point({xp,yp});
                    xp += xinc;
                }
                
                nadded = layerend;
                yp += yinc;
            }
        }

    private:
        typename Graph::VertexType v;
    };
}
#endif
