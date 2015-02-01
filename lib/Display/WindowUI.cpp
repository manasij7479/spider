#include "QtDisplay/WindowUI.hpp"
#include <QLabel>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QEvent>
#include <QKeyEvent>
#include <graph/algorithm/collections.hpp>
#include <Layout/Layout.hpp>
namespace spider
{
    WindowUI::WindowUI(GraphValue* gWrap, Layout<Graph>* l):g(gWrap), layout(l)
    {
        std::cout << "Window Open"<<std::endl;
        displayText = true;
        m_Scene = new QGraphicsScene;
        m_Scene->setSceneRect(0, 0, 800, 600);
        m_View = new QGraphicsView(this);
        m_View->setFixedSize(850, 650);
        m_View->setScene(m_Scene);
        m_View->setDragMode(QGraphicsView::DragMode::ScrollHandDrag);
        m_View->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        m_View->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        m_View->setRenderHints( QPainter::Antialiasing | QPainter::HighQualityAntialiasing );
//         m_graphScen->addLine(100, 100, 690, 190);
        changeLayout(l);
        installEventFilter(this);
//         scaleX = 1;
//         scaleY = 1;
        connect(gWrap, SIGNAL(changed()), this, SLOT(change()));
        this->show();
    }
    void WindowUI::changeLayout(Layout<Graph>* newLayout)
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
        QRadialGradient radial;
        radial.setColorAt(0, Qt::white);
        radial.setColorAt(1, Qt::green);
        radial.setRadius(10);
        

        for (auto v : graph::VertexList(newLayout->getGraph()))
        {
            Point p = newLayout->getVertex(v);
            radial.setCenter(p.x, p.y);
            radial.setFocalPoint(p.x, p.y);
            m_Scene->addEllipse(p.x - 10, p.y - 10, 20, 20, QPen(), QBrush(radial));
            
            if (displayText)
            {
                auto text = new QGraphicsTextItem();
                text->setPos(p.x - 10, p.y + 5); //TODO: Remove magic number
                text->setPlainText(v.c_str());
                m_Scene->addItem(text);
            }
        }
    }
    bool WindowUI::eventFilter(QObject* obj, QEvent* event)
    {
        if (event->type() == QEvent::KeyPress) 
        {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            qDebug("Ate key press %d", keyEvent->key());
            if (keyEvent->key() == Qt::Key_Q)
            {
                m_View->scale(1.1, 1.1);
            }
            else if (keyEvent->key() == Qt::Key_W)
            {
                m_View->scale(0.9, 0.9);
            }
            else if (keyEvent->key() == Qt::Key_Escape)
            {
                m_View->setMatrix(QMatrix());
            }
            return true;
        }
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
        changeLayout(layout);
    }

}