#ifndef SPIDER_SPIDER_SPRITE
#define SPIDER_SPIDER_SPRITE
#include <SFML/Graphics.hpp>
namespace spider
{
    class Sprite
    {
    public:
        virtual bool within(float x, float y){return false;};
        virtual bool within(sf::Vector2f p){return false;};
        virtual sf::Vector2f getPosition()=0;
        virtual sf::Sprite& get()=0;
    };
}
#endif 