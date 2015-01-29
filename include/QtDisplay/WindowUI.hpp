#ifndef SPIDER_QT_DISPLAT_WINDOW_UI_HPP
#define SPIDER_QT_DISPLAT_WINDOW_UI_HPP
#include "graph/graph.hpp"
#include "Runtime/GraphValue.hpp"
#include "Layout/Layout.hpp"
#include <iostream>
#include <QWidget>
namespace spider
{
    typedef graph::Graph<std::string, int> Graph;
    class WindowUI : QWidget
    {
        Q_OBJECT
    public:
        WindowUI(GraphValue* gWrap, Layout<Graph>* l);
        void setLayout(Layout<Graph>* newLayout);
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