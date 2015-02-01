#ifndef SPIDER_QT_DISPLAT_WINDOW_UI_HPP
#define SPIDER_QT_DISPLAT_WINDOW_UI_HPP
#include "graph/graph.hpp"
#include "Runtime/GraphValue.hpp"
#include "Layout/Layout.hpp"
#include <iostream>
#include <QWidget>
class QGraphicsView;
class QGraphicsScene;
class QMouseEvent;
class QEvent;
namespace spider
{
    typedef graph::Graph<std::string, int> Graph;
    class WindowUI : public QWidget
    {
        Q_OBJECT
    public:
        WindowUI(GraphValue* gWrap, Layout<Graph>* l);
        void changeLayout(Layout<Graph>* newLayout);
        bool isOpen(){return true;}
        GraphValue* getGraph()
        {
            return g;
        }
        bool eventFilter(QObject *obj, QEvent *event);
    private slots:
        void change();
    private:
        GraphValue* g;
        QGraphicsView* m_View;
        QGraphicsScene* m_Scene;
//         float scaleX;
//         float scaleY;
        Layout<Graph>* layout;
        bool displayText;
    };
}
#endif