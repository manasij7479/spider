#ifndef SPIDER_USER_WINDOW
#define SPIDER_USER_WINDOW
#include "Layout/CircularLayout.hpp"
#include "Display/SceneNode.hpp"
#include "Display/SceneDisplay.hpp"
#include "Display/GraphSprite.hpp"
#include "UserEnv/UserGraph.hpp"
#include "Event/EventManager.hpp"
#include "graph/graph.hpp"
namespace spider
{
    class UserWindow // size and most chacteristics are fixed for now
    {
    public:
        /*
         * Args[0] will have layout, we ignore that for now
         */
        UserWindow(spider::UserGraph* gWrap, spider::EventManager* eMgr, std::vector<std::string> Args = {}) : eventManager(eMgr)
        {
            graph::AdjacencyList<std::string, int>& gref = * gWrap->getNativeObj();
            layout = new spider::CircularLayout<graph::AdjacencyList<std::string, int>>(gref);
            gObj = new spider::GraphSprite(layout, sizex - 200, sizey);
                
            node = new spider::SceneNode(sizex, sizey);
            graph = new spider::SceneNode(sizex - 200, sizey);
            menu = new spider::SceneNode(200, sizey);
            
            node->addChild(graph, {0,0});
            graph->setObject(gObj);
            
            
            mObj = new spider::TexRectangle(200, sizey, "resource/menubar.png");
            node->addChild(menu, {1.0f*sizex - 200, 0});
            menu->setObject(mObj);
            
            b1 = new spider::SceneNode(85, 85);
            b1obj = new spider::TexRectangle(85, 85, "resource/zoom_in.png");
            menu->addChild(b1, {10,10});
            b1->setObject(b1obj);
            
            b2 = new spider::SceneNode(85, 85);
            b2obj = new spider::TexRectangle(85, 85, "resource/zoom_out.png");
            menu->addChild(b2, {105,10});
            b2->setObject(b2obj);
            
            b3 = new spider::SceneNode(85, 85);
            b3obj = new spider::TexRectangle(85, 85, "resource/fit_page.png");
            menu->addChild(b3, {10,105});
            b3->setObject(b3obj);
            
//             spider::SceneNode b4(85, 85);
//             spider::TexRectangle b4obj(85, 85, "resource/rot_left.png");
//             menu.addChild(&b4, {10, 200});
//             b4.setObject(&b4obj);
//             
//             spider::SceneNode b5(85, 85);
//             spider::TexRectangle b5obj(85, 85, "resource/rot_right.png");
//             menu.addChild(&b5, {105,200});
//             b5.setObject(&b5obj);
            
            b1obj->setCallback([&](){eventManager->reportScrollEvent(1, (sizex - 200)/2, sizey/2);});
            b2obj->setCallback([&](){eventManager->reportScrollEvent(-1, (sizex - 200)/2, sizey/2);});
            b3obj->setCallback([&](){eventManager->reportEscapeEvent();});
    
            eventManager->registerMouseClickHandler([&](float x, float y){node->handleClick(x,y);});
            
            eventManager->registerMovedHandler([&](float x, float y){gObj->handleMoved(x,y);});
            
            eventManager->registerScrollHandler([&](int t, float x, float y){gObj->handleScroll(t,x,y);});
            
            eventManager->registerReleasedHandler([&](){gObj->handleReleased();});
            eventManager->registerEscapeHandler([&](){gObj->handleEscape();});
            
            eventManager->registerRedrawHandler([&](){gObj->setLayout(layout, sizex - 200, sizey);});
            eventManager->registerRedrawHandler([&](){gObj->refreshVertexNames(&gref);});
            
            disp = new spider::SceneDisplay(node, eventManager, sizex, sizey);
        }
        bool isOpen(){return disp->isOpen();}
    private:
        const int sizex = 800, sizey = 600;
        spider::SceneNode* node, *graph, *menu, *b1, *b2, *b3;
        spider::SceneDisplay* disp;
        spider::TexRectangle* mObj, *b1obj, *b2obj, *b3obj;
        spider::CircularLayout<UserGraph::Native>* layout;
        spider::GraphSprite* gObj;
        spider::EventManager* eventManager;
    };
}
#endif
