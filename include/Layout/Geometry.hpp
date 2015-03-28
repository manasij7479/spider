#ifndef SPIDER_LAYOUT_GEOMETRY_HPP
#define SPIDER_LAYOUT_GEOMETRY_HPP
#include <vector>
#include <cmath>
/**     \brief Geometry.hpp - Header file that has collection of functions related to 2dimensional
 * ccordinate geometry for drawing graphs
 * **/
namespace spider
{
    /**
     * \brief - structure to define a point with x and y cordinates
     * **/
    struct vec2
    {
        vec2(){};
        vec2(float x_, float y_):x(x_),y(y_){};
        float x;
        float y;

    };
    typedef vec2 Point;
    
    /**
     * \brief - overloading operator '+' to add x and y coordinates of two points
     * **/
    
    inline vec2 operator+(vec2 x, vec2 y)
    {
        vec2 z;
        z.x = x.x + y.x;
        z.y = x.y + y.y;
        return z;
    }
    
    typedef std::vector<Point> Curve;
    
     /**
     * \brief - a structure defining a rectangle
     * 
     * bool within(float x, float y) - determines whether the point signified by coordinates
     * x and y is inside a rectangle or not
     * **/
    
    struct Rect
    {
        Rect(){};
        Rect(Point a, Point b): min(a), max(b){};
        Rect(float minx, float miny, float maxx, float maxy){min.x = minx; min.y = miny; max.x = maxx; max.y = maxy;};
        Point min;
        Point max;
        bool within(float x, float y)
        {
            return x >= min.x && x <=max.x && y >= min.y && y <= max.y; 
        }
    };
    
    /**
     * \brief - Returns the square of distance between two points 'a' and 'b'
     * 
     * Point a - First parameter, the first point
     * 
     * Point b - Second parameter, the second point
     * **/
    
    inline float distsquare(Point a, Point b)
    {
        float dx = a.x - b.x;
        float dy = a.y - b.y;
        return dx*dx + dy*dy;
    }
    
     /**
     * \brief - Returns the distance between two points 'a' and 'b'
     * 
     * Point a - First parameter, the first point
     * 
     * Point b - Second parameter, the second point
     * **/
    
    inline float Distance(Point a, Point b)
    {
        return std::sqrt(distsquare(a,b));
    }
    
}
#endif
