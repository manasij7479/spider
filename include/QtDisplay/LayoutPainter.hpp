#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include "Layout/Layout.hpp"
#include "Runtime/GraphValue.hpp"
#include "graph/algorithm/collections.hpp"
namespace spider
{
    class LayoutPainter
    {
    public:
        LayoutPainter(QGraphicsView* v, QGraphicsScene* s):m_View(v), m_Scene(s)
        {
            displayText = true;
            displayEdgeCost = true;
        }
        virtual void draw(Layout<GraphValue::Graph>* layout, int w, int h)
        {
            m_Scene->setSceneRect(0, 0, w, h);
            m_View->setSceneRect(0, 0, w, h);
//             layout = newLayout;
            float border = 50;
            Rect bounds = {{0 + border,0 + border},{m_View->geometry().width()  * 1.0f - border , m_View->geometry().height() * 1.0f - border}};
            m_Scene->clear();
            layout->generate(bounds);
            for (auto e : graph::EdgeList(layout->getGraph(), false))
            {
                Curve c = layout->getEdge(std::get<0>(e),std::get<1>(e));
                m_Scene->addLine(c[0].x, c[0].y, c[1].x, c[1].y);
                
                if (displayEdgeCost)
                {
                    auto text = new QGraphicsTextItem();
                    int offx = 1, offy = 0;
                    float slope = 1.0*(c[0].y - c[1].y)/(c[0].x + c[1].x);
                    if (fabs(slope) < 1)
                        offy += 10;
                    else 
                        offx += 10;
                    text->setPos((c[0].x + c[1].x)/2 + offx, (c[0].y + c[1].y)/2 + offy);
                    text->setPlainText(std::to_string(std::get<2>(e)).c_str());
                    m_Scene->addItem(text);
                }
            }
            QRadialGradient radial;
            radial.setColorAt(0, Qt::white);
            radial.setColorAt(1, Qt::green);
            radial.setRadius(10);
            

            for (auto v : graph::VertexList(layout->getGraph()))
            {
                Point p = layout->getVertex(v);
                radial.setCenter(p.x, p.y);
                radial.setFocalPoint(p.x, p.y);
                m_Scene->addEllipse(p.x - 10, p.y - 10, 20, 20, QPen(), QBrush(radial));
                
                if (displayText)
                {
                    auto text = new QGraphicsTextItem();
                    text->setPos(p.x - 10, p.y + 5); //TODO: Remove magic number
                    text->setPlainText(std::to_string(v).c_str());
                    m_Scene->addItem(text);
                }
            }
            
        }
        virtual ~LayoutPainter(){}
    private:
        QGraphicsView* m_View;
        QGraphicsScene* m_Scene;
        bool displayText;
        bool displayEdgeCost;
    };
}
