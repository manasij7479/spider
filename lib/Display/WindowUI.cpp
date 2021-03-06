#include "Layout/ManualLayout.hpp"
#include "QtDisplay/WindowUI.hpp"
#include<cmath>
#include<QString>
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
        addEdgeFlag = false;
        
        vertexTextbox = new QLineEdit();
        vertexTextbox->setMaximumWidth(90);
        weightTextbox = new QLineEdit();
        weightTextbox->setMaximumWidth(90);
        
        m_Scene = new QGraphicsScene;
        m_View = new QGraphicsView();
        lp = new LayoutPainter(m_View, m_Scene);
        auto zin = new QPushButton(QIcon("resource/zoom_in.png"), "Zoom In");
        zin->setMaximumWidth(90);
        auto zout = new QPushButton(QIcon("resource/zoom_out.png"), "Zoom Out");
        zout->setMaximumWidth(90);
        auto fit = new QPushButton(QIcon("resource/fit_page.png"), "");
        fit->setMaximumWidth(30);
        auto rotr = new QPushButton("Left");
        rotr->setMaximumWidth(90);
        auto rotl = new QPushButton("Right");
        rotl->setMaximumWidth(90);
        auto insv = new QPushButton("Insert Vertex");
        insv->setMaximumWidth(90);
        auto inse = new QPushButton("Insert Edge");
        inse->setMaximumWidth(90);
        auto movr = new QPushButton("R");
        movr->setMaximumWidth(30);
        auto movl = new QPushButton("L");
        movl->setMaximumWidth(30);
        auto movu = new QPushButton("T");
        movu->setMaximumWidth(30);
        auto movd = new QPushButton("B");
        movd->setMaximumWidth(30);
        
        menuLayout = new QGridLayout();
        menuLayout->addWidget(m_View, 0, 0, 10, 1);
        menuLayout->addWidget(zin, 0, 1);
        menuLayout->addWidget(zout, 1, 1);
        //         menuLayout->addWidget(fit, 2, 1);
        menuLayout->addWidget(rotl, 2, 1);
        menuLayout->addWidget(rotr, 3, 1);
        menuLayout->addWidget(insv, 4, 1);
        menuLayout->addWidget(inse, 5, 1);
        auto subLayout = new QGridLayout();
        subLayout->addWidget(movu, 0, 1);
        subLayout->addWidget(movl, 1, 0);
        subLayout->addWidget(fit, 1, 1);
        subLayout->addWidget(movr, 1, 2);
        subLayout->addWidget(movd, 2, 1);
        menuLayout->addLayout(subLayout, 6, 1);
        this->setLayout(menuLayout);
        
        connect(&(layout->getGraphValue()), SIGNAL(changed()), this, SLOT(change()));
        connect(zin, SIGNAL(clicked(bool)), this, SLOT(zoom_in()));
        connect(zout, SIGNAL(clicked(bool)), this, SLOT(zoom_out()));
        connect(fit, SIGNAL(clicked(bool)), this, SLOT(reset()));
        connect(rotl, SIGNAL(clicked(bool)), this, SLOT(rot_left()));
        connect(rotr, SIGNAL(clicked(bool)), this, SLOT(rot_right()));
        connect(insv, SIGNAL(clicked(bool)), this, SLOT(insert_vertex()));
        connect(inse, SIGNAL(clicked(bool)), this, SLOT(insert_edge()));
        connect(movl, SIGNAL(clicked(bool)), this, SLOT(move_left()));
        connect(movr, SIGNAL(clicked(bool)), this, SLOT(move_right()));
        connect(movu, SIGNAL(clicked(bool)), this, SLOT(move_up()));
        connect(movd, SIGNAL(clicked(bool)), this, SLOT(move_down()));
        
        m_View->setScene(m_Scene);
        m_View->setDragMode(QGraphicsView::DragMode::NoDrag);
        m_View->verticalScrollBar()->blockSignals(true);
        m_View->horizontalScrollBar()->blockSignals(true);
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
                resetSelection();
            else if(keyEvent->key() == Qt::Key_F5)
                change();
            return true;
        }
        else if (event->type() == QEvent::Resize)
        {
            change();
        }
        else if (event->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
            Point p = { static_cast<float>(mouseEvent->localPos().x()), static_cast<float>(mouseEvent->localPos().y()) };
            
            if(mouseEvent->button() == Qt::RightButton && m_View->geometry().contains(p.x, p.y))
            {
                if(!clickOnVertexFlag)
                {
                    getClickedVertex(p, clickOnVertexFlag, vertexOnHold);
                }
                else
                {
                    if(addEdgeFlag)
                    {
                        Layout* newLayout = layout;
                        bool clickOnSecondVertexFlag;
                        typename GraphValue::Graph::VertexType v;
                        getClickedVertex(p, clickOnSecondVertexFlag, v);
                        if(clickOnSecondVertexFlag)
                        {
                            newLayout->getGraph().insertEdge(vertexOnHold, v, weight);
                            if(!newLayout->getGraph().isDirected())
                                newLayout->getGraph().insertEdge(v, vertexOnHold, weight);
                            lp->setVertexSelected(false);
                            changeLayout(newLayout);
                            layout->getGraphValue().changeCallback();
                            addEdgeFlag = false;
                            clickOnVertexFlag = false;
                        }
                    }
                    else
                    {
                        lp->setVertexSelected(false);
                        QPointF qp = m_View->mapToScene(p.x, p.y);
                        changeToManualLayout(vertexOnHold, {(float)qp.x()-10,(float)qp.y()-10});
                        clickOnVertexFlag = false;
                    }
                }
                if(addVertexFlag)
                {
                    layout->getGraph().insertVertex(vertexOnHold);
                    QPointF qp = m_View->mapToScene(p.x, p.y);
                    changeToManualLayout(vertexOnHold, {(float)qp.x()-10,(float)qp.y()-10});
                    layout->getGraphValue().changeCallback();
                    addVertexFlag = false;
                }
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
    void WindowUI::getClickedVertex(Point p, bool& flag, typename GraphValue::Graph::VertexType& v)
    {
        QPointF qp = m_View->mapToScene(p.x, p.y);
        flag = false;
        for(auto i=layout->getGraph().begin();i!=layout->getGraph().end();++i)
        {
            if(pow((qp.x()-layout->getVertex(i->first).x), 2) + pow((qp.y()-layout->getVertex(i->first).y), 2) < 900)
            {
                flag = true;
                v = i->first;
                //Placeholder
                lp->selectVertex(i->first);
                lp->setVertexSelected(true);
                changeLayout(this->layout);
                //End placeholder
                break;
            }
        }
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
    void WindowUI::resetSelection()
    {
        clickOnVertexFlag = addVertexFlag = addEdgeFlag = false;
        lp->setVertexSelected(false);
        changeLayout(this->layout);
        if(!vertexTextbox->isHidden())
            vertexTextbox->hide();
        if(!weightTextbox->isHidden())
            weightTextbox->hide();
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
    void WindowUI::move_left()
    {
        m_View->translate(10, 0);
    }
    void WindowUI::move_right()
    {
        m_View->translate(-10, 0);
    }
    void WindowUI::move_up()
    {
        m_View->translate(0, 10);
    }
    void WindowUI::move_down()
    {
        m_View->translate(0, -10);
    }
    void WindowUI::insert_vertex()
    {
        vertexTextbox->clear();
        vertexTextbox->show();
        vertexTextbox->setValidator(new QIntValidator(0,std::numeric_limits<int>::max()));
        vertexTextbox->setPlaceholderText("Enter Vertex");
        //m_Scene->addWidget(textbox);
        menuLayout->addWidget(vertexTextbox, 4, 1);
        connect(vertexTextbox,SIGNAL(returnPressed()),this,SLOT(input_vertex()));
    }
    void WindowUI::input_vertex()
    {
        vertexOnHold = vertexTextbox->text().toInt();
        vertexTextbox->hide();
        addVertexFlag = true;
    }
    void WindowUI::insert_edge()
    {
        weightTextbox->clear();
        weightTextbox->show();
        weightTextbox->setValidator(new QIntValidator(0,std::numeric_limits<int>::max()));
        weightTextbox->setPlaceholderText("Enter weight");
        menuLayout->addWidget(weightTextbox, 5, 1);
        connect(weightTextbox,SIGNAL(returnPressed()),this,SLOT(input_weight()));
    }
    void WindowUI::input_weight()
    {
        weight = weightTextbox->text().toInt();
        weightTextbox->hide();
        addEdgeFlag = true;
    }
    
}
