#ifndef SPIDER_LAYOUT_ALTERNATETREELAYOUT_HPP
#define SPIDER_LAYOUT_ALTERNATETREELAYOUT_HPP
#include<algorithm>
#include<cmath>
#include "Layout/Layout.hpp"
#include "graph/algorithm/collections.hpp"
#include "graph/algorithm/enumeration.hpp"
namespace spider
{
       
    template<typename Graph>
    class AlternateTreeLayout : public Layout<Graph>
    {
        typedef Layout<Graph> Base;
    public:
        AlternateTreeLayout(Graph& g, typename Graph::VertexType v_):
        Layout<Graph>(g),v(v_)
        {
            Base::hasEdgeData = false;
        };
        
        virtual void generate(Rect bounds)
        {
            std::vector<std::pair<typename Graph::VertexType,int>> levelarray;
            levelarray.push_back(std::make_pair(v,0));
            
            graph::BreadthFirstSearch<Graph> bfs(Base::g,v);
            bfs.setp4([&](const typename Graph::VertexType& parent, const typename Graph::VertexType& x)
            {
                if(x != v)
                {
                    int level;
                    for(int i=0;i<levelarray.size();++i)
                        if(levelarray[i].first == parent)
                        {
                            level = levelarray[i].second;
                            break;
                        }
                    levelarray.push_back(std::make_pair(x,level+1));
                }
                return true;
            });
            bfs();
            
            int ecentricity = levelarray.back().second;
            
           
            float yinc = (bounds.max.y-bounds.min.y)/ecentricity;
            float yp = bounds.min.y+yinc;
            
            int nadded = 1;
            Base::points.value(v)=Point({(bounds.max.x+bounds.min.x)/2,bounds.min.y});
            for(int layer=1;layer<=ecentricity;++layer)
            {
                int layerend;
                for(int i=nadded;i<levelarray.size();++i)
                {
                    if(levelarray[i].second != layer)
                    {
                        layerend = i;
                        break;
                    }
                    if(i==levelarray.size()-1)
                    {
                        layerend=i+1;
                        break;
                    }
                }
                
                float k=120/(layerend-nadded-1);
                int deg=0;
                
                for(int i=nadded;i<layerend;++i)
                {
                    int foo=deg+k;
                    while(foo>90)
                        foo-=90;
                    float w=cos(foo);
                    if(w<0)
                      w=1-w;
                    float xp = yp*w;
                    //float yp2=yp*sin(deg+k);
                    std::cout<<xp<<" "<<yp<<" "<<w<<std::endl;
                    Base::points.value(levelarray[i].first)=Point({xp,yp});
                    deg=deg+k;
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
