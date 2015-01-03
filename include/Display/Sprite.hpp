#ifndef SPIDER_SPIDER_SPRITE
#define SPIDER_SPIDER_SPRITE
#include <SFML/Graphics.hpp>
#include "Layout/Geometry.hpp"
namespace spider
{
    class Drawable // offset could be changed to a more general renderstate, maybe borrow sf::RenderStates
    {
    public:
        virtual void draw(sf::RenderWindow* win, vec2 offset){}
        virtual void handleClick(float x, float y){}
    };
    typedef Drawable Sprite;
}
#endif 