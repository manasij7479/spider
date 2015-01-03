#include <iostream>
#include <sstream>
#include "Event/EventManager.hpp"
#include "Runtime/Runtime.hpp"
#include "X11/Xlib.h"
int main()
{
    if (XInitThreads() == 0)
    {
        std::cerr<<"Threading not fully supported, do not open more than one window.\n";
    }

    spider::Runtime rt;

    while(true)
    {
        std::string foo;
        std::getline(std::cin, foo);
        std::istringstream in(foo);
        std::vector<std::string> args;
        std::string temp;
        while(in >> temp)
            args.push_back(temp);
        rt.eval(args);
    }
}