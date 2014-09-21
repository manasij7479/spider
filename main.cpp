//This is to be currently used for testing pusposes
#include <iostream>
#include "Layout/RandomLayout.hpp"
#include "graph/util/generate.hpp"
#include "graph/algorithm/collections.hpp"
#include "Display/GraphDisplay.hpp"
int main()
{
    auto g = graph::gen::cycle(5);
    spider::RandomLayout<decltype(g)> layout(g);
    spider::Display<decltype(g)> disp(layout, 800, 600);
    
    while (true)
    {
        std::string foo;
        std::getline(std::cin, foo);
        if (foo == ".q")
        {
            disp.close();
            break;
        }
        else std::cout << foo << std::endl;
    }
}