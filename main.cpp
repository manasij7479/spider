#include <iostream>
#include "Layout/RandomLayout.hpp"
#include "Layout/ForceBasedLayout.hpp"
#include "Layout/CircularLayout.hpp"
#include "graph/util/generate.hpp"
#include "graph/algorithm/collections.hpp"
#include "Display/SceneDisplay.hpp"
#include "Display/GraphSprite.hpp"
#include "Display/TexRectangle.hpp"
#include "Display/SceneNode.hpp"
#include "External/OGDFAdapter.hpp"
#include "Event/EventManager.hpp"
#include "UserEnv/UserGraph.hpp"
int main()
{
    int sizex = 800, sizey = 600;
    auto g = graph::gen::complete(6);
    spider::CircularLayout<decltype(g)> layout(g);
    spider::GraphSprite<decltype(g)> gObj(&layout, sizex - 200, sizey);

    spider::SceneNode node(sizex, sizey);
    spider::SceneNode graph(sizex - 200, sizey);
    spider::SceneNode menu(200, sizey);
    
    node.addChild(&graph, {0,0});
    graph.setObject(&gObj);
    
//     spider::MenuSprite mObj(spider::Rect(sizex - 200 ,0 , sizex , sizey));
    spider::TexRectangle mObj(200, sizey, "resource/menubar.png");
    node.addChild(&menu, {1.0f*sizex - 200, 0});
    menu.setObject(&mObj);
    
    
    spider::EventManager eMgr;
//     eMgr.registerMouseClickHandler([](float x, float y){std::cout<<x<<' '<<y<<std::endl;});
    
    auto clicked = [&](float x, float y){gObj.handleClick(x,y);};
    eMgr.registerMouseClickHandler(clicked);
    
    auto moved = [&](float x, float y){gObj.handleMoved(x,y);};
    eMgr.registerMovedHandler(moved);
    
    auto scrolled = [&](int t, float x, float y){gObj.handleScroll(t,x,y);};
    eMgr.registerScrollHandler(scrolled);
    
    eMgr.registerReleasededHandler(std::bind(&spider::GraphSprite<decltype(g)>::handleReleased, &gObj));
    eMgr.registerEscapeHandler(std::bind(&spider::GraphSprite<decltype(g)>::handleEscape, &gObj));
    
    
    spider::SceneDisplay disp(&node, &eMgr, sizex, sizey);
    while(disp.isOpen())
    {
        std::string foo;
        spider::ForceBasedLayout<decltype(g)> l(g);
        std::getline(std::cin, foo);
        if (foo == ".q")
            eMgr.reportCloseEvent();
        else if (foo == "change")
            gObj.setLayout(&l, sizex - 200, sizey);
        else if(foo == "toggle")
            gObj.toggleTextDisplay();
        else std::cout<<foo;
    }
}