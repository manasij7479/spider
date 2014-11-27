//This is to be currently used for testing pusposes
#include <iostream>
#include "UserEnv/UserGraph.hpp"
int main()
{
    spider::UserGraph g;
    g.setCallback([](){std::cout<<"foo\n";});
    g.insertVertex({"1"});
    g.insertVertex({"2"});
    g.insertEdge({"1", "2", "1"});
}