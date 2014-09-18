#ifndef SPIDER_LAYOUT_GEOMETRY_HPP
#define SPIDER_LAYOUT_GEOMETRY_HPP
#include <vector>
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
}
#endif