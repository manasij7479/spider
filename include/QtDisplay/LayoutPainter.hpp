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
            op_displayEdgeCost = false;
            op_useGradient = true;
            op_vertexColoring = false;
            op_edgeColoring = false;
            op_vertexSelected = false;
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
            
//             bool hasColor = layout->getGraphValue().hasVertexAttribute("color");
//             bool hasCn = layout->getGraphValue().hasAttribute("cn");
            
            
            if (op_edgeColoring)
            {
                auto ecstate = graph::minEdgeColoring(layout->getGraph());
                for (auto e : graph::EdgeList(layout->getGraph(), false))
                {
                    auto p = std::make_pair(std::get<0>(e),std::get<1>(e));
                    int color = ecstate.getColorMap()[p];
                    edgeColors[p] = genColor(color, ecstate.noOfColorsUsed());
                }
            }
            if (op_vertexColoring)
            {
                auto vcstate =graph::WelshPowellColoring(layout->getGraph());
                for (auto v : graph::VertexList(layout->getGraph()))
                {
                    int color = vcstate.getColorMap()[v];
                    vertexColors[v] = genColor(color, vcstate.noOfColorsUsed());
                }
            }
            for (auto e : graph::EdgeList(layout->getGraph(), false))
            {
                Curve c = layout->getEdge(std::get<0>(e),std::get<1>(e));
                if (std::get<0>(e) == std::get<1>(e))
                {
                    m_Scene->addEllipse(c[0].x -10 , c[0].y -40, 20, 40);
                    continue;
                    //FIXME: Coloring is skipped
                }
                auto p = std::make_pair(std::get<0>(e), std::get<1>(e));
                if (edgeColors.find(p) != edgeColors.end())
                {
                    m_Scene->addLine(c[0].x, c[0].y, c[1].x, c[1].y, QPen(edgeColors[p]));
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
//                     std::cout<<dir1.p1().x()<<" "<<dir1.p1().y()<<std::endl;
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
                    
                if (vertexColors.find(v) != vertexColors.end())
                {
                    m_Scene->addEllipse(p.x - 10, p.y - 10, 20, 20 , QPen(), QBrush(vertexColors[v]));
                }
                else if (op_useGradient)
                {
                    radial.setCenter(p.x, p.y);
                    radial.setFocalPoint(p.x, p.y);
                    m_Scene->addEllipse(p.x - 10, p.y - 10, 20, 20, QPen(), QBrush(radial));
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
                if(op_vertexSelected && selectedVertex == v)
                    m_Scene->addEllipse(p.x - 7.5, p.y - 7.5, 15, 15 , QPen(), QBrush(QColor(Qt::black))); // does not work if color of vertex is black/dark
                                                                                                           //another color for selection may be suggested
                                                                                                           //or any other approach
            }
            
        }
        void markVertex(int vertex, std::string col)
        {
            vertexColors[vertex] = QColor(col.c_str());
        }
        void markEdge(int x, int y, std::string col, bool undirected = true)
        {
            
            edgeColors[std::make_pair(x, y)] = QColor(col.c_str());
            if (undirected)
                edgeColors[std::make_pair(y, x)] = QColor(col.c_str());
        }
        void selectVertex(typename GraphValue::Graph::VertexType v) {selectedVertex = v;}
        virtual ~LayoutPainter(){}
    private:
        QGraphicsView* m_View;
        QGraphicsScene* m_Scene;
        bool op_displayText;
        bool op_displayEdgeCost;
        bool op_useGradient;
        bool op_vertexColoring;
        bool op_edgeColoring;
        bool op_vertexSelected;
        QColor genColor(int i, int n)     ////TODO avoid generation of black color
        {
            QColor col;
            col.setHsv(i* 360/n, 255, 255);
            return col;
        }
        std::map<int, QColor> vertexColors;
        std::map<std::pair<int, int>, QColor> edgeColors;
        typename GraphValue::Graph::VertexType selectedVertex;
    public:
         void setDisplayText(bool b){op_displayText = b;}
         void setDisplayEdgeCost(bool b){op_displayEdgeCost = b;}
         void setUseGradient(bool b){op_useGradient = b;}
         void setVertexColoring(bool b){vertexColors.clear();op_vertexColoring = b;}
         void setEdgeColoring(bool b){edgeColors.clear();op_edgeColoring = b;}
         void setVertexSelected(bool b){op_vertexSelected = b;}
    };
}
