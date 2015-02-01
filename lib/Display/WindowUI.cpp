#include "QtDisplay/WindowUI.hpp"
#include <QLabel>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QEvent>
#include <QKeyEvent>
#include <QGridLayout>
#include <QPushButton>
#include <graph/algorithm/collections.hpp>
#include <Layout/Layout.hpp>
namespace spider
{
    WindowUI::WindowUI(GraphValue* gWrap, Layout<Graph>* l):g(gWrap), layout(l)
    {
        std::cout << "Window Open"<<std::endl;
        displayText = true;
        m_Scene = new QGraphicsScene;
        m_View = new QGraphicsView();

        auto zin = new QPushButton(QIcon("resource/zoom_in.png"), "Zoom In");
        auto zout = new QPushButton(QIcon("resource/zoom_out.png"), "Zoom Out");
        auto fit = new QPushButton(QIcon("resource/fit_page.png"), "Fit Page");
        auto rotr = new QPushButton("Left");
        auto rotl = new QPushButton("Right");
        auto layout = new QGridLayout();
        layout->addWidget(m_View, 0, 0, 10, 1);
        layout->addWidget(zin, 0, 1);
        layout->addWidget(zout, 1, 1);
        layout->addWidget(fit, 2, 1);
        layout->addWidget(rotl, 3, 1);
        layout->addWidget(rotr, 4, 1);
        this->setLayout(layout);
        
        connect(zin, SIGNAL(clicked(bool)), this, SLOT(zoom_in()));
        connect(zout, SIGNAL(clicked(bool)), this, SLOT(zoom_out()));
        connect(fit, SIGNAL(clicked(bool)), this, SLOT(reset()));
        connect(rotl, SIGNAL(clicked(bool)), this, SLOT(rot_left()));
        connect(rotr, SIGNAL(clicked(bool)), this, SLOT(rot_right()));
        
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
        m_Scene->setSceneRect(0, 0, this->geometry().width(), this->geometry().height());
        m_View->setSceneRect(0, 0, this->geometry().width(), this->geometry().height());
        std::cout << "Layout Set"<<std::endl;
        layout = newLayout;
        float border = 50;
        Rect bounds = {{0 + border,0 + border},{this->geometry().width() * 1.0f - border , this->geometry().height() * 1.0f - border}};
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
                zoom_in();
            else if (keyEvent->key() == Qt::Key_W)
                zoom_out();
            else if (keyEvent->key() == Qt::Key_Escape)
                reset();
            return true;
        }
        else if (event->type() == QEvent::Resize)
        {
            change();
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
    void WindowUI::zoom_in()
    {
        m_View->scale(1.1, 1.1);
    }

    void WindowUI::zoom_out()
    {
        m_View->scale(0.9, 0.9);
    }
    void WindowUI::reset()
    {
        m_View->setMatrix(QMatrix());
    }
    void WindowUI::rot_left()
    {
        m_View->rotate(45);
    }
    void WindowUI::rot_right()
    {
        m_View->rotate(-45);
    }


}