/**
 * \brief TreeLayout.hpp - Header file that contains functions to generate Binary Tree Layout
 * 
 * Binary Tree Layout for drawing a graph- The layout starts at the root and plots the adjacent
 * vertices in the form of tree datastructure. Each node can have a maximum of 2 child nodes 
 * and a minimum of 0 child nodes
 * **/#ifndef SPIDER_LAYOUT_BINARYTREELAYOUT_HPP
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
        /**
         * \brief - generates x and y coordinates of each vertex
         * 
         * @param Rect bounds - Parameter, contains the x and y coordinates of the boundary of the drawing area
         * **/
        virtual void generate(Rect bounds)
        {
            std::map<int, std::vector<V>> vertexAtLevel;
            std::map<V, int> xindex;
            int ecentricity = graph::EcentricityList<GraphValue::Graph>(*(g.data), false).find(root)->second + 1;
            int yinc = (bounds.max.y + bounds.min.y) / (ecentricity-1);
            std::map<V, bool> isVisited;
            for(auto i=g.data->begin();i!=g.data->end();++i)
                isVisited[i->first] = false;
            
            points.value(root) = Point({(bounds.min.x+bounds.max.x)/2, bounds.min.y});
            vertexAtLevel[0].push_back(root);
            xindex[root] = 0;
            isVisited[root] = true;
            
            for(int level=0; level<ecentricity-1; ++level)
            {
                auto vlist = vertexAtLevel[level];
                int noVertexAtLevel = vlist.size();
                
                for(int i=0; i<noVertexAtLevel; ++i)
                {
                    int xinc = (bounds.max.x - bounds.min.x) / (pow(2, level+1) - 1);
                    auto elist = graph::OutVertexList<GraphValue::Graph>(*(g.data), vlist[i]);
                    std::sort(elist.begin(),elist.end(),[&](V x,V y){return g.data->weight(vlist[i],x)<g.data->weight(vlist[i],y);});
                    for(auto j=elist.begin(); j!=elist.end(); ++j)
                    {
                        if(!isVisited[*j])
                        {
                            if(g.data->weight(vlist[i],*j) == 1)
                                xindex[*j] = 2*xindex[vlist[i]];
                            else
                                xindex[*j] = 2*xindex[vlist[i]] + 1;
                            
                            points.value(*j) = Point({bounds.min.x+xindex[*j]*xinc, bounds.min.y+(level+1)*yinc});
                            vertexAtLevel[level+1].push_back(*j);
                            isVisited[*j] = true;
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
