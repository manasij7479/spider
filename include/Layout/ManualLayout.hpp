#ifndef SPIDER_MANUAL_LAYOUT_HPP
#define SPIDER_MANUAL_LAYOUT_HPP
#include "Layout/Layout.hpp"

namespace spider
{
    class ManualLayout : public Layout
    {
    public:
        ManualLayout(Layout oldLayout, typename GraphValue::Graph::VertexType v, Point p)
        :Layout(oldLayout.getGraphValue())
        {
            setVertexAttribute(oldLayout.getVertexAttribute());
            points.value(v) = p;
            hasEdgeData = false;
        };

        virtual void generate(Rect bounds) {}
    private:
        graph::VertexAttribute<GraphValue::Graph,Point> attribute;
    };
}
#endif
