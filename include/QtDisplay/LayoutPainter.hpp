#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QColor>
#include "Layout/Layout.hpp"
#include "Runtime/GraphValue.hpp"
#include "Runtime/TypeOps.hpp"
#include "graph/algorithm/collections.hpp"
/**
 * \brief LayoutPainter.hpp - Header File that helps in drawing different
 * visualization aspects
 * **/
namespace spider
{
	/**
	 * \brief - Layout Painter retrives coordinate data for each vertex and
	 * draws it on the screen. It is the basic framework to render coordinate
	 * data on screen.
	 * **/
    class LayoutPainter
    {
    public:
		/**
		 * \brief - Constructor
		 * 
		 * @param QGraphicsView* v - First Parameter, a graphic view attribute of Qt
		 * 
		 * @param QGraphicsScene* s - Second Parameter, a graphic scene attribute of Qt
		 * **/
        LayoutPainter(QGraphicsView* v, QGraphicsScene* s):m_View(v), m_Scene(s)
        {
            op_displayText = true;
            op_displayEdgeCost = true;
            op_useGradient = false;
            op_useVertexColorAttrib = true;
        }
        /**
         * \brief - A function to draw the graph and its attributes on screen
         * 
         * @param Layout* layout - First Parameter, the layout to be used to plot a graph
         * 
         * @param int w - Second Parameter, the width of the screen
         * 
         * @param int h - Third Parameter, the height of the screen
         * **/
        virtual void draw(Layout* layout, int w, int h)
        {
            m_Scene->setSceneRect(0, 0, w, h);
            m_View->setSceneRect(0, 0, w, h);
//             layout = newLayout;
            float border = 50;
            Rect bounds = {{0 + border,0 + border},{m_View->geometry().width()  * 1.0f - border , m_View->geometry().height() * 1.0f - border}};
            m_Scene->clear();
            layout->generate(bounds);
            
            bool hasColor = layout->getGraphValue().hasVertexAttribute("color");
            bool hasCn = layout->getGraphValue().hasAttribute("cn");
            
            for (auto e : graph::EdgeList(layout->getGraph(), false))
            {
                Curve c = layout->getEdge(std::get<0>(e),std::get<1>(e));
                m_Scene->addLine(c[0].x, c[0].y, c[1].x, c[1].y);
                
                if (op_displayEdgeCost)
                {
                    auto text = new QGraphicsTextItem();
                    int offx = 0, offy = 0;
//                     float slope = 1.0*(c[0].y - c[1].y)/(c[0].x + c[1].x);
//                     if (fabs(slope) < 1)
//                         offy += 10;
//                     else 
//                         offx += 10;
                    text->setPos((c[0].x + c[1].x)/2 + offx, (c[0].y + c[1].y)/2 + offy);
                    text->setPlainText(std::to_string(std::get<2>(e)).c_str());
                    m_Scene->addItem(text);
                }
            }
            QRadialGradient radial;
            if (op_useGradient)
            {
                radial.setColorAt(0, Qt::white);
                radial.setColorAt(1, Qt::green);
                radial.setRadius(10);
            }    

            for (auto v : graph::VertexList(layout->getGraph()))
            {
                Point p = layout->getVertex(v);
                if (op_useGradient)
                {
                    radial.setCenter(p.x, p.y);
                    radial.setFocalPoint(p.x, p.y);
                    m_Scene->addEllipse(p.x - 10, p.y - 10, 20, 20, QPen(), QBrush(radial));
                }
                else if (op_useVertexColorAttrib && hasColor)
                {
                    int c = geti(layout->getGraphValue().getVertexAttribute("color", v))->data;
                    int n = layout->getGraph().order();
                    if (hasCn)
                        n = geti(layout->getGraphValue().getGraphAttribs()->data["cn"])->data;
                    auto col = genColor(c, n);
                    m_Scene->addEllipse(p.x - 10, p.y - 10, 20, 20 , QPen(), QBrush(QColor(col)));
                }
                else
                {
                    m_Scene->addEllipse(p.x - 10, p.y - 10, 20, 20 , QPen(), QBrush(QColor(Qt::green)));
                }
                if (op_displayText)
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
        bool op_displayText;
        bool op_displayEdgeCost;
        bool op_useGradient;
        bool op_useVertexColorAttrib;
        QColor genColor(int i, int n)
        {
            QColor col;
            col.setHsv(i* 360/n, 255, 255);
            return col;
        }
    public:
         bool& displayText(){return op_displayText;}///<to display text on screen
         bool& displayEdgeCost(){return op_displayEdgeCost;}///<to display edge cost above edges
         bool& useGradient(){return op_useGradient;}///<to use gradients
         bool& useVertexColorAttrib(){return op_useVertexColorAttrib;}///<to use vertex coloring attribute
    };
}
