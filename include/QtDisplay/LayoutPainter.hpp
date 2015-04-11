#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QColor>
#include <cmath>
#include "Layout/Layout.hpp"
#include "Runtime/GraphValue.hpp"
#include "Runtime/TypeOps.hpp"
#include "graph/algorithm/operations.hpp"
#include "graph/algorithm/collections.hpp"
#include "graph/algorithm/coloring.hpp"
namespace spider
{
    class LayoutPainter
    {
    public:
        LayoutPainter(QGraphicsView* v, QGraphicsScene* s):m_View(v), m_Scene(s)
        {
            op_displayText = true;
            op_displayEdgeCost = false;
            op_useGradient = true;
            op_vertexColoring = false;
            op_edgeColoring = false;
        }
        virtual void draw(Layout* layout, int w, int h)
        {
            m_Scene->setSceneRect(0, 0, w, h);
            m_View->setSceneRect(0, 0, w, h);
//             layout = newLayout;
            float border = 50;
            Rect bounds = {{0 + border,0 + border},{m_View->geometry().width()  * 1.0f - border , m_View->geometry().height() * 1.0f - border}};
            m_Scene->clear();
            layout->generate(bounds);
            
//             bool hasColor = layout->getGraphValue().hasVertexAttribute("color");
//             bool hasCn = layout->getGraphValue().hasAttribute("cn");
            
            graph::ColorState<graph::AdjacencyList<int, int>, std::pair<int, int>>* ecstate;
            if (op_edgeColoring)
                ecstate = new graph::ColorState<graph::AdjacencyList<int, int>, std::pair<int, int>>(graph::minEdgeColoring(layout->getGraph()));
            graph::ColorState<graph::AdjacencyList<int, int>, int>* vcstate;
            if (op_vertexColoring)
                vcstate = new graph::ColorState<graph::AdjacencyList<int, int>, int> (graph::WelshPowellColoring(layout->getGraph()));
            
            for (auto e : graph::EdgeList(layout->getGraph(), false))
            {
                Curve c = layout->getEdge(std::get<0>(e),std::get<1>(e));
                if (op_edgeColoring)
                {
                    int color = ecstate->getColorMap()[std::make_pair(std::get<0>(e),std::get<1>(e))];
                    m_Scene->addLine(c[0].x, c[0].y, c[1].x, c[1].y, QPen(genColor(color, ecstate->noOfColorsUsed())));
                }
                else
                    m_Scene->addLine(c[0].x, c[0].y, c[1].x, c[1].y);
                if(layout->getGraph().isDirected())
                {
                    int startindex,endindex,dist,startx,starty,endx,endy;
                    if(graph::isAdjacent(layout->getGraph(), std::get<0>(e), std::get<1>(e)))
                    {
                        startindex = 1;
                        endindex =0;
                    }
                    else
                    {
                        startindex = 0;
                        endindex = 1;
                    }
                    dist = sqrt(powl(c[0].x - c[1].x, 2) + powl(c[0].y - c[1].y, 2));
                    int m=dist-20,n=20;
                    startx = ((dist-10)*c[startindex].x + 10*c[endindex].x)/dist;
                    starty = ((dist-10)*c[startindex].y + 10*c[endindex].y)/dist;
                    endx = (m*c[startindex].x + n*c[endindex].x)/(m+n);
                    endy = (m*c[startindex].y + n*c[endindex].y)/(m+n);
                    QLineF edge(c[startindex].x,c[startindex].y,c[endindex].x,c[endindex].y);
                    QLineF dir1(startx,starty,endx,endy);
                    QLineF dir2(startx,starty,endx,endy);
                    dir1.setAngle(edge.angle()+45);
                    dir2.setAngle(edge.angle()-45);
                    std::cout<<dir1.p1().x()<<" "<<dir1.p1().y()<<std::endl;
                    m_Scene->addLine(dir1);
                    m_Scene->addLine(dir2);
                }
                
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
                else if (op_vertexColoring)
                {
                    
                    auto col = genColor(vcstate->getColorMap()[v], vcstate->noOfColorsUsed());
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
        bool op_vertexColoring;
        bool op_edgeColoring;
        QColor genColor(int i, int n)
        {
            QColor col;
            col.setHsv(i* 360/n, 255, 255);
            return col;
        }
    public:
         bool& displayText(){return op_displayText;}
         bool& displayEdgeCost(){return op_displayEdgeCost;}
         bool& useGradient(){return op_useGradient;}
         bool& useVertexColorAttrib(){return op_useVertexColorAttrib;}
         bool& useVertexColoring(){return op_vertexColoring;}
         bool& useEdgeColoring(){return op_edgeColoring;}
    };
}
