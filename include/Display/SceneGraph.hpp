#ifndef SPIDER_SCENE_GRAPH_HPP
#define SPIDER_SCENE_GRAPH_HPP
#include "Layout/Geometry.hpp"
#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>
namespace spider
{
    class Drawable
    {
    public:
        virtual void draw(sf::RenderWindow* win, vec2 offset){}
    };
    
    class SceneNode
    {
    public:
        void draw(sf::RenderWindow* win, vec2 offset)
        {
            if(object!=nullptr)
                object->draw(win, offset + translation);
            for(auto& child : children)
                child->draw(win, offset + translation);
        }
        
    private:
        std::string name;
        Rect bounds;
        vec2 translation;
        std::vector<SceneNode*> children;
        SceneNode* parent;
        Drawable* object; // may be null
    };
}
#endif