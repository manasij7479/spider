//This is to be currently used for testing pusposes
#include <iostream>
#include "Layout/RandomLayout.hpp"
#include "Layout/ForceBasedLayout.hpp"
#include "Layout/CircularLayout.hpp"
#include "graph/util/generate.hpp"
#include "graph/algorithm/collections.hpp"
#include "Display/GraphDisplay.hpp"
#include "Display/GraphSprite.hpp"
#include "Display/SceneGraph.hpp"
#include "External/OGDFAdapter.hpp"
#include "Event/Event.hpp"
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
    auto g = graph::gen::complete(6);
    spider::CircularLayout<decltype(g)> layout(g);
    sf::RenderWindow window(sf::VideoMode(800,600), "Display");
    spider::GraphSpriteObject<decltype(g)> test(&layout, 800, 600);
    spider::EventManager mgr;
    mgr.registerMouseClickHandler([](float x, float y){std::cout<<x<<' '<<y<<std::endl;});
    while(window.isOpen())
    {   
        window.clear(sf::Color::White);
        test.draw(&window, {0,0});
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::MouseButtonPressed)
                mgr.reportMouseClickEvent(event.mouseButton.x,event.mouseButton.y);
        }
        window.display();
    }
}