#include <iostream>
#include <sstream>
#include "Event/EventManager.hpp"
#include "Runtime/Runtime.hpp"
#include "Runtime/Statement.hpp"
#include "X11/Xlib.h"
/*ISSUES and TODO:
 * Closed window names remain in symbol table.
 * In general, allow destruction.
 * Input not inverse transformed when interacting with graphs (can be avoided now).
 * Needs manually editable graph on screen.
 * Proper Error messages
 * Language Implementation (At this moment, the IR is taken as input and directly executed)
 */
int main()
{
    if (XInitThreads() == 0)
    {
        std::cerr<<"Threading not fully supported, do not open more than one window.\n";
    }
    std::cout << "*** Spider IR Executor ***"<<std::endl;;
    spider::Runtime rt;
    while (true)
    {
        std::cout << ">> ";
        spider::Statement input(std::cin);
        try
        {
            if (! input.isEmpty())
                rt.eval(input);
        }
        catch (std::exception& e)
        {
            std::cerr << "ERROR: " << e.what();
        }
    }
}