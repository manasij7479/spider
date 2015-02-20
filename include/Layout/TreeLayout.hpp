/**
 * \brief TreeLayout.hpp - Header file that contains functions to generate
 * Tree Layout for drawing a graph. The layout starts at the root and plots the adjacent
 * vertices in the form of tree datastructure.
 * **/
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
        
        /**
         * \brief - generates x and y coordinates of each vertex
         * 
         * Rect bounds - Parameter, contains the x and y coordinates of 
         * the boundary of the drawing area
         * **/
        virtual void generate(Rect bounds)
        {
            std::vector<std::pair<typename Graph::VertexType,int>> levelarray;
            levelarray.push_back(std::make_pair(v,0));
            
            graph::BreadthFirstSearch<Graph> bfs(Base::g,v);
            bfs.setp4([&](const typename Graph::VertexType& parent, const typename Graph::VertexType& x)
            {
                if(x != v)
                {
                    int level = 0;
                    for(uint i=0;i<levelarray.size();++i)
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
                int layerend = 0;
                for(uint i=nadded;i<levelarray.size();++i)
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
                
                float xinc = (bounds.max.x-bounds.min.x)/(layerend-nadded-1);
                float xp = bounds.min.x;
                for(int i=nadded;i<layerend;++i)
                {
//                     std::cout<<i<<" "<<patharray[i].back()<<std::endl;
                    Base::points.value(levelarray[i].first)=Point({xp,yp});
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
