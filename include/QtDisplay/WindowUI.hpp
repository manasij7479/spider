#ifndef SPIDER_QT_DISPLAT_WINDOW_UI_HPP
#define SPIDER_QT_DISPLAT_WINDOW_UI_HPP
#include "graph/graph.hpp"
#include "Runtime/GraphValue.hpp"
#include "Layout/Layout.hpp"
#include <QWidget>
class QGraphicsView;
class QGraphicsScene;
class QMouseEvent;
class QEvent;
/** \brief - to display all the different components of visualization window.
 * **/
namespace spider
{
  
    class LayoutPainter;
    /**
     * \brief - Class to control and display the different components of visualization window.
     * 
     * The different components consists of the graph displaying component, tool bar and menu bar.
     * The tool bar supports functions like zoom in, zoom out, rotate left, rotate right, fit to page.
     * **/
    class WindowUI : public QWidget
    {
        Q_OBJECT
    public:
	/** \brief - Constructor
	 * 
	 * @param GraphValue* gWrap - First Parameter, a GraphValue object. Contains different graph attributes.
	 * 
	 * @param Layout* l - Second Parameter, the layout in which the graph is to be displayed.
	 **/
        WindowUI(GraphValue* gWrap, Layout* l);
	/** \brief - function to change layout of the displayed graph
	 *
	 * @param Layout* newLayout - Parameter, the new layout in which the graph is to be displayed.
	 **/
        void changeLayout(Layout* newLayout);
	/**
	 * \brief - function to check if the window is open.
	 * Returns true if window is open, false otherwise.
	 * **/
        bool isOpen(){return true;}
        /** \brief - function to get a graph
	 *
	 * @returns GraphValue* - attributes of the graph.
	 **/
        GraphValue* getGraph()
        {
            return g;
        }
        /**
	 * \brief - to filter events.
	 * 
	 * @param QObject* obj - First Parameter, a Qt object
	 * 
	 * @param QEvent* event - Second Parameter, a Qt event.
	 * **/
        bool eventFilter(QObject *obj, QEvent *event);
	/**
	 * \brief - a function to get Layout getLayoutPainter
	 * 
	 * @returns LayoutPainter* - attributes of Layout Painter.
	 * **/
        LayoutPainter* getLayoutPainter(){return lp;}
        void changeCallback(){emit change();}
    private slots:
        void change();
        void zoom_in();
        void zoom_out();
        void reset();
        void rot_right();
        void rot_left();
        void insert_vertex();
        void input_vertex();
    private:
        GraphValue* g;
        QGraphicsView* m_View;
        QGraphicsScene* m_Scene;
//         float scaleX;
//         float scaleY;
        Layout* layout;
        LayoutPainter* lp;
        QLineEdit* textbox;
        QGridLayout* menuLayout; // For adding items dynamically
        
        bool clickOnVertexFlag;
        bool addVertexFlag;
        
        typename GraphValue::Graph::VertexType vertexOnHold;
        void changeToManualLayout(typename GraphValue::Graph::VertexType v, Point p);
        void getClickedVertex(Point p, bool& flag, typename GraphValue::Graph::VertexType& v);
    };
}
#endif
