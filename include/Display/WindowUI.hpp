#ifndef SPIDER_USER_WINDOW
#define SPIDER_USER_WINDOW
#include "Layout/CircularLayout.hpp"
#include "Display/SceneNode.hpp"
#include "Display/SceneDisplay.hpp"
#include "Display/GraphSprite.hpp"
#include "Display/TexRectangle.hpp"
#include "Event/EventManager.hpp"
#include "graph/graph.hpp"
#include "NewRuntime/GraphValue.hpp"
namespace spider
{
    class UserWindowUI
    {
    public:
        UserWindowUI(GraphValue* gWrap) 
        {
            eventManager = new EventManager();

            graph::AdjacencyList<std::string, int>& gref = * gWrap->data;
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
            gWrap->setCallback([&](){eventManager->reportRedrawEvent();});
        }
        bool isOpen(){return disp->isOpen();}
        void eval(std::vector<std::string> args)
        {
            //TODO: save image, change layout..things like that
        }
        ~UserWindowUI()
        {
            //maybe tell node to delete its children instead ?
//             delete node;
//             delete graph;
//             delete menu; 
//             delete b1;
//             delete b2;
//             delete b3;
//             delete disp;
//             delete mObj;
//             delete b1obj;
//             delete b2obj;
//             delete b3obj;
//             delete layout;
//             delete gObj;
//             delete eventManager;
        }
    private:
        static const int sizex = 800, sizey = 600;
        spider::SceneNode* node, *graph, *menu, *b1, *b2, *b3;
        spider::SceneDisplay* disp;
        spider::TexRectangle* mObj, *b1obj, *b2obj, *b3obj;
        spider::CircularLayout<GraphValue::Graph>* layout;
        spider::GraphSprite* gObj;
        spider::EventManager* eventManager;
    };
}
#endif
