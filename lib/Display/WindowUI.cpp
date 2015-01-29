#include "QtDisplay/WindowUI.hpp"
namespace spider
{
    WindowUI::WindowUI(GraphValue* gWrap, Layout<Graph>* l):g(gWrap)
    {
        std::cout << "Window Open"<<std::endl;
    }
    void WindowUI::setLayout(Layout<Graph>* newLayout)
    {
//             gObj->setLayout(newLayout, sizex - 200, sizey);
        std::cout << "Layout Set"<<std::endl;
    }
}