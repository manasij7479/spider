#ifndef SPIDER_LAYOUT_BINARYTREELAYOUT_HPP
#define SPIDER_LAYOUT_BINARYTREELAYOUT_HPP
#include<cmath>
#include<algorithm>
#include "Layout/Layout.hpp"
#include "graph/algorithm/collections.hpp"
#include "graph/algorithm/enumeration.hpp"
namespace spider
{
    
    class BinaryTreeLayout : public Layout
    {
    public:
        typedef typename GraphValue::Graph::VertexType V;
        BinaryTreeLayout(GraphValue& g, typename GraphValue::Graph::VertexType root_):
        Layout(g),root(root_)
        {
            hasEdgeData = false;
        };
        
        virtual void generate(Rect bounds)
        {
            std::map<int, std::vector<V>> vertexAtLevel;
            int ecentricity = graph::EcentricityList<GraphValue::Graph>(*(g.data), false).find(root)->second + 1;
            int yinc = (bounds.max.y + bounds.min.y) / (ecentricity-1);
            std::map<V, bool> isVisited;
            for(auto i=g.data->begin();i!=g.data->end();++i)
                isVisited[i->first] = false;
            
            points.value(root) = Point({(bounds.min.x+bounds.max.x)/2, bounds.min.y});
            vertexAtLevel[0].push_back(root);
            isVisited[root] = true;
            
            for(int level=0; level<ecentricity-1; ++level)
            {
                auto vlist = vertexAtLevel[level];
                int noVertexAtLevel = vlist.size();
                
                for(int i=0; i<noVertexAtLevel; ++i)
                {
                    int xinc = (bounds.max.x - bounds.min.x) / (pow(2, level+1) - 1);
                    for(auto j=g.data->nbegin(vlist[i]); j!=g.data->nend(vlist[i]); ++j)
                    {
                        if(!isVisited[j->first])
                        {
                            if(j->second == 1)
                            {
                                points.value(j->first) = Point({bounds.min.x+(2*i)*xinc, bounds.min.y+(level+1)*yinc});
                                vertexAtLevel[level+1].push_back(j->first);
                                isVisited[j->first] = true;
                            }
                            else
                            {
                                points.value(j->first) = Point({bounds.min.x+(2*i+1)*xinc, bounds.min.y+(level+1)*yinc});
                                vertexAtLevel[level+1].push_back(j->first);
                                isVisited[j->first] = true;
                            }
                        }
                    }
                }
            }
        }
    private:
        GraphValue::Graph::VertexType root;
    };
}
#endif
