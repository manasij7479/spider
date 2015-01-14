#ifndef SPIDER_WINDOW_VALUE_HPP
#define SPIDER_WINDOW_VALUE_HPP
#include "Display/WindowUI.hpp"
#include "Runtime/Type.hpp"
namespace spider
{
    class WindowValue : public Value
    {
    public:
        WindowValue(GraphValue* g):Value(VType::Window)
        {
            data = new UserWindowUI(g);
        }
        UserWindowUI* data;
    };
}
#endif