//This is to be currently used for testing pusposes
#include <iostream>
#include "Layout/Layout.hpp"
#include "graph/util/generate.hpp"
#include "graph/algorithm/collections.hpp"
int main()
{
    auto g = graph::gen::cycle(5);
    spider::RandomLayout<decltype(g)> layout(g);
    layout.generate({{-2,-2},{2,2}});
    for (auto v : graph::VertexList(g))
    {
        auto p = layout.getVertex(v);
        std::cout << v << '\t' << p.x << ','<< p.y <<std::endl;
    }
}