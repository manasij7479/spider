#include <iostream>
#include <sstream>
#include "Event/EventManager.hpp"
#include "Runtime/Runtime.hpp"
int main()
{
    
    spider::EventManager eMgr;

    spider::Runtime rt(&eMgr);

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