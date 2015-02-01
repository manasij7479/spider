#ifndef SPIDER_WINDOW_VALUE_HPP
#define SPIDER_WINDOW_VALUE_HPP
#include "QtDisplay/WindowUI.hpp"
#include "Runtime/Type.hpp"
#include "Layout/Layout.hpp"
#include "../../main/mainwindow.h"
namespace spider
{
    class WindowValue : public Value
    {
        Q_OBJECT
    public:
        WindowValue(GraphValue* g, Layout<Graph>* l): Value(VType::Window)
        {
            connect(this, SIGNAL(create(GraphValue*, Layout<Graph>*)), mainWin, SLOT(create(GraphValue*, Layout<Graph>*)));
            emit create(g,l);
        }
        WindowUI* data;
    signals:
        void create(GraphValue*, Layout<Graph>*);
    };

}
#endif