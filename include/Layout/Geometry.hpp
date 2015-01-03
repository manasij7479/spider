#ifndef SPIDER_LAYOUT_GEOMETRY_HPP
#define SPIDER_LAYOUT_GEOMETRY_HPP
#include <vector>
#include <cmath>
#include <SFML/System/Vector2.hpp>
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
        Rect(float minx, float miny, float maxx, float maxy){min.x = minx; min.y = miny; max.x = maxx; max.y = maxy;};
        Point min;
        Point max;
        bool within(float x, float y)
        {
            return x >= min.x && x <=max.x && y >= min.y && y <= max.y; 
        }
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
    
    sf::Vector2f sfvec2(float x, float y)
    {
        return sf::Vector2f(x,y);
    }
}
#endif