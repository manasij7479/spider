#ifndef SPIDER_DISPLAY_TEX_RECT_HPP
#define SPIDER_DISPLAY_TEX_RECT_HPP
#include "Display/Sprite.hpp"
#include "Layout/Geometry.hpp"
#include <iostream>
namespace spider
{
    class TexRectangle : public Drawable
    {
    public:
        TexRectangle(int sizex, int sizey, std::string filename):texfilename(filename), texloaded(true)
        {
            tex.setSmooth(true);
            if (!tex.loadFromFile(texfilename)) 
                texloaded = false;
            
            quad[0]= sf::Vertex(sf::Vector2f(0, 0));
            quad[1]= sf::Vertex(sf::Vector2f(0, sizey));
            quad[2]= sf::Vertex(sf::Vector2f(sizex, sizey));
            quad[3]= sf::Vertex(sf::Vector2f(sizex, 0));
            
            quad[0].texCoords = sf::Vector2f(0, 0);
            quad[1].texCoords = sf::Vector2f(tex.getSize().x, 0);
            quad[2].texCoords = sf::Vector2f(tex.getSize().x, tex.getSize().y);
            quad[3].texCoords = sf::Vector2f(0, tex.getSize().y);
        };
        void draw(sf::RenderWindow* win, vec2 offset)
        {
            auto transform = sf::Transform::Identity;
            transform.translate(offset.x, offset.y);
            sf::RenderStates state(transform);
            state.texture = &tex;
            win->draw(quad, 4, sf::Quads, state);
        }
    private:
        sf::Vertex quad[4];
        std::string texfilename;
        sf::Texture tex;
        bool texloaded;
    };
}
#endif