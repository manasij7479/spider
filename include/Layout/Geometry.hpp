#ifndef SPIDER_LAYOUT_GEOMETRY_HPP
#define SPIDER_LAYOUT_GEOMETRY_HPP
#include <vector>
#include <cmath>
//switch to glm if this proves insufficient and inextensible
namespace spider
{
    struct vec2
    {
        vec2(){};
        vec2(float x_, float y_):x(x_),y(y_){};
        float x;
        float y;

    };
    typedef vec2 Point;
    
    vec2 operator+(vec2 x, vec2 y)
    {
        vec2 z;
        z.x = x.x + y.x;
        z.y = x.y + y.y;
        return z;
    }
    
    typedef std::vector<Point> Curve;
    
    struct Rect
    {
        Rect(){};
        Rect(Point a, Point b): min(a), max(b){};
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
    
}
#endif