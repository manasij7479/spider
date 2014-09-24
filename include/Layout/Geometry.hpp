#ifndef SPIDER_LAYOUT_GEOMETRY_HPP
#define SPIDER_LAYOUT_GEOMETRY_HPP
#include <vector>
#include <cmath>
//switch to glm if this proves insufficient and inextensible
namespace spider
{
    struct vec2
    {
        float x;
        float y;
    };
    typedef vec2 Point;
    
    typedef std::vector<Point> Curve;
    
    struct Rect
    {
        Point min;
        Point max;    
    };
    
    float distsquare(Point a, Point b)
    {
        float dx = a.x - b.x;
        float dy = a.y - b.y;
        return dx*dx + dy*dy;
    }
    
    float Distance(Point a, Point b)
    {
        return std::sqrt(distsquare(a,b));
    }
    bool Within(Rect bounds, Point p) // move this to Geometry
    {
        return  p.x > bounds.min.x && p.x < bounds.max.x && p.y > bounds.min.y && p.y < bounds.max.y;;
    }
    
}
#endif