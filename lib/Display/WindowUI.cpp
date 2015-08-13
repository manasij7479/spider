#include "../../include/Layout/ManualLayout.hpp"
#include "QtDisplay/WindowUI.hpp"
#include<cmath>
#include <QLabel>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QEvent>
#include <QKeyEvent>
#include <QGridLayout>
#include <QPushButton>
#include <graph/algorithm/collections.hpp>
#include "Layout/Layout.hpp"
#include "QtDisplay/LayoutPainter.hpp"
namespace spider
{
    WindowUI::WindowUI(GraphValue* gWrap, Layout* l):g(gWrap), layout(l)
    {
        clickOnVertexFlag = false;
        addVertexFlag = false;
        
        m_Scene = new QGraphicsScene;
        m_View = new QGraphicsView();
        lp = new LayoutPainter(m_View, m_Scene);
        auto zin = new QPushButton(QIcon("resource/zoom_in.png"), "Zoom In");
        auto zout = new QPushButton(QIcon("resource/zoom_out.png"), "Zoom Out");
        auto fit = new QPushButton(QIcon("resource/fit_page.png"), "Fit Page");
        auto rotr = new QPushButton("Left");
        auto rotl = new QPushButton("Right");
        auto insv = new QPushButton("Insert Vertex");

        auto layout = new QGridLayout();
        layout->addWidget(m_View, 0, 0, 10, 1);
        layout->addWidget(zin, 0, 1);
        layout->addWidget(zout, 1, 1);
        layout->addWidget(fit, 2, 1);
        layout->addWidget(rotl, 3, 1);
        layout->addWidget(rotr, 4, 1);
        layout->addWidget(insv, 5, 1);
        this->setLayout(layout);
        
        connect(zin, SIGNAL(clicked(bool)), this, SLOT(zoom_in()));
        connect(zout, SIGNAL(clicked(bool)), this, SLOT(zoom_out()));
        connect(fit, SIGNAL(clicked(bool)), this, SLOT(reset()));
        connect(rotl, SIGNAL(clicked(bool)), this, SLOT(rot_left()));
        connect(rotr, SIGNAL(clicked(bool)), this, SLOT(rot_right()));
        connect(insv, SIGNAL(clicked(bool)), this, SLOT(insert_vertex()));
        
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
    void WindowUI::changeLayout(Layout* newLayout)
    {
        layout = newLayout;
        lp->draw(layout, this->geometry().width(), this->geometry().height());
    }
    bool WindowUI::eventFilter(QObject* obj, QEvent* event)
    {
        if (event->type() == QEvent::KeyPress) 
        {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
//             qDebug("Ate key press %d", keyEvent->key());
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
        else if (event->type() == QEvent::MouseButtonDblClick)
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
            Point p = {static_cast<float>(mouseEvent->localPos().x()), 
                        static_cast<float>(mouseEvent->localPos().y())};
            
            if(!clickOnVertexFlag)
            {
                for(auto i=g->data->begin();i!=g->data->end();++i)
                {
                    if(pow((p.x-layout->getVertex(i->first).x),2) + pow((p.y-layout->getVertex(i->first).y),2) < 900)
                    {
                        clickOnVertexFlag = true;
                        vertexOnHold = i->first;
                        break;
                    }
                }
            }
            else
            {
                changeToManualLayout(vertexOnHold, {p.x-10,p.y-10});
                clickOnVertexFlag = false ;
            }
            if(addVertexFlag)
            {
                layout->getGraph().insertVertex(vertexOnHold);
                changeToManualLayout(vertexOnHold, {p.x-10,p.y-10});
                addVertexFlag = false;
            }
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
    void WindowUI::changeToManualLayout(typename GraphValue::Graph::VertexType v, Point p)
    {
        Layout* newLayout = new ManualLayout(*layout,v,p);
        changeLayout(newLayout);
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
    void WindowUI::insert_vertex()
    {
        textbox = new QLineEdit();
        textbox->setValidator(new QIntValidator(0,std::numeric_limits<int>::max()));
        textbox->setPlaceholderText("Enter Vertex");
        m_Scene->addWidget(textbox);
        connect(textbox,SIGNAL(returnPressed()),this,SLOT(input_vertex()));
    }
    void WindowUI::input_vertex()
    {
        vertexOnHold = textbox->text().toInt();
        textbox->hide();
        addVertexFlag = true;
    }
    
    

}