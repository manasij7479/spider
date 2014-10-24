//This is to be currently used for testing pusposes
#include <iostream>
#include "Layout/RandomLayout.hpp"
#include "Layout/ForceBasedLayout.hpp"
#include "Layout/CircularLayout.hpp"
#include "graph/util/generate.hpp"
#include "graph/algorithm/collections.hpp"
#include "Display/GraphDisplay.hpp"
#include "Display/GraphSprite.hpp"
#include "External/OGDFAdapter.hpp"
int main()
{
    auto g = graph::gen::complete(6);
    spider::CircularLayout<decltype(g)> layout(g);
    spider::ForceBasedLayout<decltype(g)> layout2(g);
    
    spider::GraphSprite<decltype(g)> gs(&layout);
    spider::Display<decltype(g)> disp(&gs, 800, 600);
    
    while (disp.isOpen())
    {
        std::string foo;
        std::getline(std::cin, foo);
        if (foo == ".q")
        {
            disp.close();
            break;
        }
        if (foo == "change")
        {
            gs.setLayout(&layout2);
        }
        else std::cout << foo << std::endl;
    }
//     graph::Graph<int,bool> g;
//     g.insertVertex(1);
//     g.insertVertex(2);
//     g.insertEdge(1,2,true);
//     auto gnew = spider::ConvertToOGDF(g);
//     gnew.writeGML("test.gml");
    
}