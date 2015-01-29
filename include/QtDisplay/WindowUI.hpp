#ifndef SPIDER_QT_DISPLAT_WINDOW_UI_HPP
#define SPIDER_QT_DISPLAT_WINDOW_UI_HPP
#include "graph/graph.hpp"
#include "Runtime/GraphValue.hpp"
#include "Layout/Layout.hpp"
#include <iostream>
namespace spider
{
    typedef graph::Graph<std::string, int> Graph;
    class WindowUI
    {
    public:
        WindowUI(GraphValue* gWrap, Layout<Graph>* l):g(gWrap)
        {
            std::cout << "Window Open"<<std::endl;
        }
        void setLayout(Layout<Graph>* newLayout)
        {
//             gObj->setLayout(newLayout, sizex - 200, sizey);
            std::cout << "Layout Set"<<std::endl;
        }
        bool isOpen(){return true;}
        GraphValue* getGraph()
        {
            return g;
        }
    private:
        GraphValue* g;
    };
}
#endif