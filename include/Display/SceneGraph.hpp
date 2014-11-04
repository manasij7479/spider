#ifndef SPIDER_SCENE_GRAPH_HPP
#define SPIDER_SCENE_GRAPH_HPP
#include "Layout/Geometry.hpp"
#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>
namespace spider
{
    class Drawable // offset could be changed to a more general renderstate, maybe borrow sf::RenderStates
    {
    public:
        virtual void draw(sf::RenderWindow* win, vec2 offset){}
    };
    
    class SceneNode
    {
    public:
        SceneNode(Rect bounds_, vec2 offset = {0,0}, SceneNode* p = nullptr){}
        void setObject(Drawable* obj)
        {
            object = obj;
        }
        void addChild(SceneNode* n)
        {
            n->setParent(this);
            children.push_back(n);
        }
        void setParent(SceneNode* p)
        {
            parent = p;
        }
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