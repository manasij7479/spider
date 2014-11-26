#ifndef SPIDER_SCENE_GRAPH_HPP
#define SPIDER_SCENE_GRAPH_HPP
#include "Layout/Geometry.hpp"
#include "Event/EventManager.hpp"
#include "Display/Sprite.hpp"
#include <vector>
namespace spider
{
    
    class SceneNode : public Drawable
    {
    public:
        SceneNode(int x, int y)
        {
            sizex = x;
            sizey = y;
            object = nullptr;
        }
        void setObject(Drawable* obj)
        {
            object = obj;
        }
        void addChild(SceneNode* n, vec2 offset)
        {
            n->setParent(this);
            children.push_back({n,offset});
        }
        void setParent(SceneNode* p)
        {
            parent = p;
        }
        void draw(sf::RenderWindow* win, vec2 offset)
        {
            if(object!=nullptr)
                object->draw(win, offset);
            for(auto& child : children)
                child.first->draw(win, offset + child.second);
        }
    private:
        std::string name;
        int sizex, sizey;
        std::vector<std::pair<SceneNode*, vec2>> children;
        SceneNode* parent;
        Drawable* object; // may be null

    };
}
#endif