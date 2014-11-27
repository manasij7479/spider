#ifndef SPIDER_SCENE_GRAPH_HPP
#define SPIDER_SCENE_GRAPH_HPP
#include "Layout/Geometry.hpp"
#include "Event/EventManager.hpp"
#include "Display/Sprite.hpp"
#include <vector>
#include <iostream>
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
        void handleClick(float x, float y)
        {
//             std::cout<<x <<' '<<y <<std::endl;
            if (object)
                object->handleClick(x,y);
            for(auto pair : children)
            {
                if (x >= pair.second.x && x <= pair.second.x + pair.first->sizex 
                    && y >= pair.second.y && y <= pair.second.y + pair.first->sizey)
                        pair.first->handleClick(x-pair.second.x, y-pair.second.y);
            }
            
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