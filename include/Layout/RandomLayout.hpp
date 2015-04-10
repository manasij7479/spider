#ifndef SPIDER_RANDOM_LAYOUT_HPP
#define SPIDER_RANDOM_LAYOUT_HPP
#include "Layout/Layout.hpp"
/**
 * \brief RandomLayout.hpp - Header file that contains function to generate a Random Layout.
 * 
 * Random Centered Layout for drawing a graph - The layout plots the nodes randomly, against a
 * fixed center.
 * **/
namespace spider
{
    /**
     * \brief - Random Layout for drawing a graph - This layout plots the vertices randomly.
     * **/
    class RandomLayout : public Layout
    {
    public:
        /**
         * \brief - Constructor
         * 
         * @param GraphValue& g - First Parameter, a graph object and attributes
         * 
         * @param float m = 2.5f - Second Parameter, Increasing this means the points will be spread out,
         * but also increases the chances of lying out of bounds
         * **/
        RandomLayout(GraphValue& g, float m = 2.5f):
            Layout(g),
            twister(rd()),
            modifier(m)
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
            Point center = {(bounds.max.x+bounds.min.x)/2, (bounds.max.y+bounds.min.y)/2};
            
            float xspan = center.x - bounds.min.x;
            float yspan = center.y - bounds.min.y;
            
            Point stddev={xspan/modifier,yspan/modifier};
            
            std::normal_distribution<> x(center.x, stddev.x),y(center.y, stddev.y);
            
            for(auto it=getGraph().begin();it!=getGraph().end();++it)
            {
                float xp=x(twister);
                float yp=y(twister);
                points.value(it->first)=Point({xp,yp});
            }

            
        }
    private:
        std::random_device rd;
        std::mt19937 twister;
        float modifier; 
        
    };
}
#endif
