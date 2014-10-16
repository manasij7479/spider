//This is to be currently used for testing pusposes
#include <iostream>
#include "Layout/RandomLayout.hpp"
#include "Layout/ForceBasedLayout.hpp"
#include "graph/util/generate.hpp"
#include "graph/algorithm/collections.hpp"
#include "Display/GraphDisplay.hpp"
#include "External/OGDFAdapter.hpp"
int main()
{
//     auto g = graph::gen::complete(5);
//     spider::ForceBasedLayout<decltype(g)> layout(g);
//     spider::Display<decltype(g)> disp(layout, 800, 600);
//     
//     while (true)
//     {
//         std::string foo;
//         std::getline(std::cin, foo);
//         if (foo == ".q")
//         {
//             disp.close();
//             break;
//         }
//         else std::cout << foo << std::endl;
//     }
    graph::Graph<int,bool> g;
    g.insertVertex(1);
    g.insertVertex(2);
    g.insertEdge(1,2,true);
    auto gnew = spider::ConvertToOGDF(g);
    gnew.writeGML("test.gml");
    
}