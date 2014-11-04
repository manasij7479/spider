#ifndef SPIDER_DISPLAY_MENU_SPRITE_HPP
#define SPIDER_DISPLAY_MENU_SPRITE_HPP
#include "Display/Sprite.hpp"
#include "Layout/Geometry.hpp"
#include <iostream>
namespace spider
{
    class MenuSprite : public Drawable
    {
    public:
        MenuSprite(Rect bounds_): bounds(bounds_)
        {
            
            quad[0]= sf::Vertex(sf::Vector2f(bounds.min.x, bounds.min.y));
            quad[1]= sf::Vertex(sf::Vector2f(bounds.min.x, bounds.max.y));
            quad[2]= sf::Vertex(sf::Vector2f(bounds.max.x, bounds.max.y));
            quad[3]= sf::Vertex(sf::Vector2f(bounds.max.x, bounds.min.y));
            
            std::cout<< (bounds.min.x)<<','<< (bounds.min.y)<<std::endl;
            std::cout<< (bounds.min.x)<<','<< (bounds.max.y)<<std::endl;
            std::cout<< (bounds.max.x)<<','<< (bounds.max.y)<<std::endl;
            std::cout<< (bounds.max.x)<<','<< (bounds.min.y)<<std::endl;
            
            quad[0].texCoords = sf::Vector2f(0, 0);
            quad[1].texCoords = sf::Vector2f(20, 0);
            quad[2].texCoords = sf::Vector2f(20, 20);
            quad[3].texCoords = sf::Vector2f(0, 20);
        };
        void draw(sf::RenderWindow* win, vec2 offset)
        {
            sf::RenderStates state(sf::Transform::Identity);
            sf::Texture tex;
            tex.setSmooth(true);
            if (!tex.loadFromFile("resource/menubar.png")) 
                ; // do nothing..or maybe a log entry later
            else
            state.texture = &tex;
            win->draw(quad, 4, sf::Quads, state);
        }
    private:
        Rect bounds;
        sf::Vertex quad[4];
    };
}
#endif