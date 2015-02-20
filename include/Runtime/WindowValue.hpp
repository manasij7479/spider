#ifndef SPIDER_WINDOW_VALUE_HPP
#define SPIDER_WINDOW_VALUE_HPP
#include "QtDisplay/WindowUI.hpp"
#include "Runtime/Type.hpp"
#include "Layout/Layout.hpp"
#include "QtDisplay/MainWindow.hpp"
namespace spider
{
    class WindowValue : public Value
    {
        Q_OBJECT
    public:
        WindowValue(GraphValue* g, Layout<GraphValue::Graph>* l): Value(VType::Window)
        {
            connect(this, SIGNAL(create(GraphValue*, Layout<GraphValue::Graph>*)), mainWin, SLOT(create(GraphValue*, Layout<GraphValue::Graph>*)));
            emit create(g,l);
        }
        WindowUI* data;
    signals:
        void create(GraphValue*, Layout<GraphValue::Graph>*);
    };

}
#endif