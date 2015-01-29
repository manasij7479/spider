#include "QtDisplay/WindowUI.hpp"
#include <QLabel>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QEvent>
#include <QKeyEvent>
#include <graph/algorithm/collections.hpp>
#include <Layout/Layout.hpp>
namespace spider
{
    WindowUI::WindowUI(GraphValue* gWrap, Layout<Graph>* l):g(gWrap), layout(l)
    {
        std::cout << "Window Open"<<std::endl;
        m_Scene = new QGraphicsScene;
        m_Scene->setSceneRect(0, 0, 800, 600);

        m_View = new QGraphicsView(this);
        m_View->setFixedSize(850, 650);
        m_View->setScene(m_Scene);
        m_View->setDragMode(QGraphicsView::DragMode::ScrollHandDrag);
        m_View->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        m_View->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//         m_graphScen->addLine(100, 100, 690, 190);
        setLayout(l);
        installEventFilter(this);
//         scaleX = 1;
//         scaleY = 1;
        this->show();
    }
    void WindowUI::setLayout(Layout<Graph>* newLayout)
    {
        std::cout << "Layout Set"<<std::endl;
        layout = newLayout;
        float border = 15;
        Rect bounds = {{0 + border,0 + border},{800 * 1.0f - border , 600 * 1.0f - border}};
        m_Scene->clear();
        newLayout->generate(bounds);
        for (auto e : graph::EdgeList(newLayout->getGraph(), false))
        {
            Curve c=newLayout->getEdge(std::get<0>(e),std::get<1>(e));
            m_Scene->addLine(c[0].x, c[0].y, c[1].x, c[1].y);
        }
    }
    bool WindowUI::eventFilter(QObject* obj, QEvent* event)
    {
//         if (event->type() == QEvent::KeyPress) 
//         {
//             QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
//             qDebug("Ate key press %d", keyEvent->key());
//             if (keyEvent->key() == Qt::Key_Q)
//             {
//                 m_View->scale(1.1, 1.1);
//             }
//             else if (keyEvent->key() == Qt::Key_W)
//             {
//                 m_View->scale(0.9, 0.9);
//             }
//             return true;
//         }
//         else if (event->type() == QEvent::MouseButtonPress)
//         {
//             QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
//             m_View->centerOn(mouseEvent->x(), mouseEvent->y());
//         }
//         else 
//         {
//             // standard event processing
//             return QObject::eventFilter(obj, event);
//         }
//         return true;
//     }
        return QObject::eventFilter(obj, event);
    }
    void WindowUI::change()
    {
        setLayout(layout);
    }

}