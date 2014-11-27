#include <iostream>
#include <sstream>
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
    spider::GraphSprite gObj(&layout, sizex - 200, sizey);

    spider::SceneNode node(sizex, sizey);
    spider::SceneNode graph(sizex - 200, sizey);
    spider::SceneNode menu(200, sizey);
    
    node.addChild(&graph, {0,0});
    graph.setObject(&gObj);
    
    spider::TexRectangle mObj(200, sizey, "resource/menubar.png");
    node.addChild(&menu, {1.0f*sizex - 200, 0});
    menu.setObject(&mObj);
    
    
    spider::EventManager eMgr;
    
    eMgr.registerMouseClickHandler([&](float x, float y){gObj.handleClick(x,y);});
    
    eMgr.registerMovedHandler([&](float x, float y){gObj.handleMoved(x,y);});
    
    eMgr.registerScrollHandler([&](int t, float x, float y){gObj.handleScroll(t,x,y);});
    
    eMgr.registerReleasededHandler([&](){gObj.handleReleased();});
    eMgr.registerEscapeHandler([&](){gObj.handleEscape();});
    
    eMgr.registerRedrawHandler([&](){gObj.setLayout(&layout, sizex - 200, sizey);});
    eMgr.registerRedrawHandler([&](){gObj.refreshVertexNames(&g);});
    
    spider::SceneDisplay disp(&node, &eMgr, sizex, sizey);
    spider::UserGraph gWrap(&g);
    gWrap.setCallback([&](){eMgr.reportRedrawEvent();});
    
    while(disp.isOpen())
    {
        std::string foo;
        spider::ForceBasedLayout<decltype(g)> l(g);
        std::getline(std::cin, foo);
        if (foo == ".q")
            eMgr.reportCloseEvent();
        else if(foo == "toggleText")
            gObj.toggleTextDisplay();
        else
        {
            std::istringstream in(foo);
            std::vector<std::string> args;
            std::string temp;
            while(in >> temp)
                args.push_back(temp);
            gWrap.evalCommand(args);
        }
    }
}