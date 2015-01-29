#include "QtDisplay/WindowUI.hpp"
#include <QLabel>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <graph/algorithm/collections.hpp>
#include <Layout/Layout.hpp>
namespace spider
{
    WindowUI::WindowUI(GraphValue* gWrap, Layout<Graph>* l):g(gWrap)
    {
        std::cout << "Window Open"<<std::endl;
        m_Scene = new QGraphicsScene;
        m_Scene->setSceneRect(0, 0, 800, 600);

        m_View = new QGraphicsView(this);
        m_View->setFixedSize(850, 650);
        m_View->setScene(m_Scene);
        m_View->setDragMode(QGraphicsView::DragMode::ScrollHandDrag);
//         m_graphScen->addLine(100, 100, 690, 190);
        float border = 15;
        Rect bounds = {{0 + border,0 + border},{800 * 1.0f - border , 600 * 1.0f - border}};
        l->generate(bounds);
        for (auto e : graph::EdgeList(l->getGraph(), false))
        {
            Curve c=l->getEdge(std::get<0>(e),std::get<1>(e));
            m_Scene->addLine(c[0].x, c[0].y, c[1].x, c[1].y);
        }
        this->show();
    }
    void WindowUI::setLayout(Layout<Graph>* newLayout)
    {
        std::cout << "Layout Set"<<std::endl;
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
}