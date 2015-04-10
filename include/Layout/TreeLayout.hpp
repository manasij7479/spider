<<<<<<< HEAD
=======
/**
 * \brief TreeLayout.hpp - Header file that contains functions to generate Tree Layout.
 * 
 * Tree Layout for drawing a graph - The layout starts at the root and plots the adjacent
 * vertices in the form of tree datastructure.
 * **/
>>>>>>> master
#ifndef SPIDER_LAYOUT_TREELAYOUT_HPP
#define SPIDER_LAYOUT_TREELAYOUT_HPP
#include<algorithm>
#include "Layout/Layout.hpp"
#include "graph/algorithm/collections.hpp"
#include "graph/algorithm/enumeration.hpp"
/**
 * \brief TreeLayout.hpp - Header file that contains functions to generate Tree Layout.
 * **/
namespace spider
{
    template <typename V>
    bool sortComparison(std::vector<V> i, std::vector<V> j) { return (i.size()<j.size()); }
    /**
     * \brief - Tree Layout for drawing a graph. The layout starts at the root and plots the adjacent
     * vertices in the form of tree datastructure. This layout is especially useful in plotting graphs
     * such as any trees, star graph etc
     * **/
    class TreeLayout : public Layout
    {
    public:
        /**
         * \brief - Constructor
         * 
         * @param GraphValue& g - First Parameter, a graph object and attributes
         * 
         * @param typename GraphValue::Graph::VertexType v_ - Second Parameter, the root vertex. 
         * **/
        TreeLayout(GraphValue& g, typename GraphValue::Graph::VertexType v_):
        Layout(g),v(v_)
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
            std::vector<std::pair<GraphValue::Graph::VertexType,int>> levelarray;
            levelarray.push_back(std::make_pair(v,0));
            
            graph::BreadthFirstSearch<GraphValue::Graph> bfs(getGraph(),v);
            bfs.setp4([&](const typename GraphValue::Graph::VertexType& parent, const typename GraphValue::Graph::VertexType& x)
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
            points.value(v)=Point({(bounds.max.x+bounds.min.x)/2,bounds.min.y});
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
                    points.value(levelarray[i].first)=Point({xp,yp});
                    xp += xinc;
                }
                
                nadded = layerend;
                yp += yinc;
            }
        }
    private:
        GraphValue::Graph::VertexType v;
    };
}
#endif
