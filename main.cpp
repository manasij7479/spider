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
    auto g = graph::gen::complete_bipartite(3,3);
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
    
    spider::SceneNode b1(85, 85);
    spider::TexRectangle b1obj(85, 85, "resource/zoom_in.png");
    menu.addChild(&b1, {10,10});
    b1.setObject(&b1obj);
    
    spider::SceneNode b2(85, 85);
    spider::TexRectangle b2obj(85, 85, "resource/zoom_out.png");
    menu.addChild(&b2, {105,10});
    b2.setObject(&b2obj);
    
    spider::SceneNode b3(85, 85);
    spider::TexRectangle b3obj(85, 85, "resource/fit_page.png");
    menu.addChild(&b3, {10,105});
    b3.setObject(&b3obj);
    
    spider::SceneNode b4(85, 85);
    spider::TexRectangle b4obj(85, 85, "resource/rot_left.png");
    menu.addChild(&b4, {10, 200});
    b4.setObject(&b4obj);
    
    spider::SceneNode b5(85, 85);
    spider::TexRectangle b5obj(85, 85, "resource/rot_right.png");
    menu.addChild(&b5, {105,200});
    b5.setObject(&b5obj);
    
    spider::EventManager eMgr;
    b1obj.setCallback([&](){eMgr.reportScrollEvent(1, (sizex - 200)/2, sizey/2);});
    b2obj.setCallback([&](){eMgr.reportScrollEvent(-1, (sizex - 200)/2, sizey/2);});
    b3obj.setCallback([&](){eMgr.reportEscapeEvent();});
    
    eMgr.registerMouseClickHandler([&](float x, float y){node.handleClick(x,y);});
    
    eMgr.registerMovedHandler([&](float x, float y){gObj.handleMoved(x,y);});
    
    eMgr.registerScrollHandler([&](int t, float x, float y){gObj.handleScroll(t,x,y);});
    
    eMgr.registerReleasedHandler([&](){gObj.handleReleased();});
    eMgr.registerEscapeHandler([&](){gObj.handleEscape();});
    
    eMgr.registerRedrawHandler([&](){gObj.setLayout(&layout, sizex - 200, sizey);});
    eMgr.registerRedrawHandler([&](){gObj.refreshVertexNames(&g);});
    
    spider::SceneDisplay disp(&node, &eMgr, sizex, sizey);
    spider::UserGraph gWrap(&g);
    gWrap.setCallback([&](){eMgr.reportRedrawEvent();});
    
    while(disp.isOpen())
    {
        std::string foo;
        std::getline(std::cin, foo);
        if (foo == ".q")
            eMgr.reportCloseEvent();
        else if(foo == "toggleText")
            gObj.toggleTextDisplay();
        else if (foo == "rot")
            gObj.handleRotate(1);
//         else if (foo[0] == 'c')
//         {
//             std::istringstream in(foo);
//             std::vector<std::string> args;
//             std::string temp;
//             while(in >> temp)
//                 args.push_back(temp);
//             args.erase(args.begin());
//             gWrap = spider::UserGraph(args);
//             gWrap.setCallback([&](){eMgr.reportRedrawEvent();});
//             gWrap.setNativeObj(gWrap.getNativeObj());
//         }
        else if(foo!="")
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