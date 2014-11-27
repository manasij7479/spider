//This is to be currently used for testing pusposes
#include <iostream>
#include "UserEnv/UserGraph.hpp"
int main()
{
    spider::UserGraph g;
    g.setCallback([](){std::cout<<"foo\n";});
    g.setNativeObj(g.getNativeObj());
}