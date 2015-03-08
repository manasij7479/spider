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
    class LayoutPainter;
    class WindowUI : public QWidget
    {
        Q_OBJECT
    public:
        WindowUI(GraphValue* gWrap, Layout<GraphValue::Graph>* l);
        void changeLayout(Layout<GraphValue::Graph>* newLayout);
        bool isOpen(){return true;}
        GraphValue* getGraph()
        {
            return g;
        }
        bool eventFilter(QObject *obj, QEvent *event);
        LayoutPainter* getLayoutPainter(){return lp;}
    private slots:
        void change();
        void zoom_in();
        void zoom_out();
        void reset();
        void rot_right();
        void rot_left();
    private:
        GraphValue* g;
        QGraphicsView* m_View;
        QGraphicsScene* m_Scene;
//         float scaleX;
//         float scaleY;
        Layout<GraphValue::Graph>* layout;
        LayoutPainter* lp;
    };
}
#endif