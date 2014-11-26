//This is to be currently used for testing pusposes
#include <iostream>
#include "Layout/RandomLayout.hpp"
#include "Layout/ForceBasedLayout.hpp"
#include "Layout/CircularLayout.hpp"
#include "graph/util/generate.hpp"
#include "graph/algorithm/collections.hpp"
#include "Display/SceneDisplay.hpp"
#include "Display/GraphSprite.hpp"
#include "Display/MenuSprite.hpp"
#include "Display/SceneNode.hpp"
#include "External/OGDFAdapter.hpp"
#include "Event/EventManager.hpp"
int main()
{
    int sizex = 800, sizey = 600;
    auto g = graph::gen::complete(6);
    spider::CircularLayout<decltype(g)> layout(g);
    spider::GraphSprite<decltype(g)> gObj(&layout, sizex - 200, sizey);

    spider::SceneNode node(spider::Rect(0,0,sizex, sizey));
    spider::SceneNode graph(spider::Rect(0,0,sizex - 200 , sizey));
    spider::SceneNode menu(spider::Rect(sizex - 200 , 0 , sizex , sizey));
    
    node.addChild(&graph);
    graph.setObject(&gObj);
    
    spider::MenuSprite mObj(spider::Rect(sizex - 200 ,0 , sizex , sizey));
    node.addChild(&menu);
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
        else std::cout<<foo;
    }
}