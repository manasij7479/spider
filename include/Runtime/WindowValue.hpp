#ifndef SPIDER_WINDOW_VALUE_HPP
#define SPIDER_WINDOW_VALUE_HPP
#include "Display/WindowUI.hpp"
#include "Runtime/Type.hpp"
#include "Layout/Layout.hpp"
namespace spider
{
    class WindowValue : public Value
    {
    public:
        WindowValue(GraphValue* g, Layout<GraphValue::Graph>* l):Value(VType::Window)
        {
            data = new UserWindowUI(g, l);
        }
        UserWindowUI* data;
    };
}
#endif