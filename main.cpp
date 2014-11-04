//This is to be currently used for testing pusposes
#include <iostream>
#include "Layout/RandomLayout.hpp"
#include "Layout/ForceBasedLayout.hpp"
#include "Layout/CircularLayout.hpp"
#include "graph/util/generate.hpp"
#include "graph/algorithm/collections.hpp"
#include "Display/SceneDisplay.hpp"
#include "Display/GraphSprite.hpp"
#include "Display/SceneNode.hpp"
#include "External/OGDFAdapter.hpp"
#include "Event/EventManager.hpp"
int main()
{
//     auto g = graph::gen::complete(6);
//     spider::CircularLayout<decltype(g)> layout(g);
//     spider::ForceBasedLayout<decltype(g)> layout2(g);
//     
//     spider::GraphSprite<decltype(g)> gs(&layout);
//     spider::Display<decltype(g)> disp(&gs, 800, 600);
//     
//     while (disp.isOpen())
//     {
//         std::string foo;
//         std::getline(std::cin, foo);
//         if (foo == ".q")
//         {
//             disp.close();
//             break;
//         }
//         if (foo == "change")
//         {
//             gs.setLayout(&layout2);
//         }
//         else std::cout << foo << std::endl;
//     }
//     graph::Graph<int,bool> g;
//     g.insertVertex(1);
//     g.insertVertex(2);
//     g.insertEdge(1,2,true);
//     auto gnew = spider::ConvertToOGDF(g);
//     gnew.writeGML("test.gml");
    
//     auto g = graph::gen::complete(6);
//     spider::CircularLayout<decltype(g)> layout(g);
//     sf::RenderWindow window(sf::VideoMode(800,600), "Display");
//     spider::GraphSpriteObject<decltype(g)> test(&layout, 800, 600);
//     spider::EventManager mgr;
//     mgr.registerMouseClickHandler([](float x, float y){std::cout<<x<<' '<<y<<std::endl;});
//     while(window.isOpen())
//     {   
//         window.clear(sf::Color::White);
//         test.draw(&window, {0,0});
//         sf::Event event;
//         while (window.pollEvent(event))
//         {
//             if (event.type == sf::Event::MouseButtonPressed)
//                 mgr.reportMouseClickEvent(event.mouseButton.x,event.mouseButton.y);
//         }
//         window.display();
//     }

    int sizex = 800, sizey = 600;
    auto g = graph::gen::complete(6);
    spider::CircularLayout<decltype(g)> layout(g);
    spider::GraphSprite<decltype(g)> gObj(&layout, sizex, sizey);

    spider::SceneNode node(spider::Rect(0,0,sizex, sizey));
    spider::SceneNode graph(spider::Rect(0,0,sizex,sizey));
    node.addChild(&graph);
    graph.setObject(&gObj);
    
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
        std::getline(std::cin, foo);
        if (foo == ".q")
            eMgr.reportCloseEvent();
        std::cout<<foo;
    }
}