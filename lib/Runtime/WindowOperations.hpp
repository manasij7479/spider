#include "Runtime/WindowValue.hpp"
#include "Runtime/TypeOps.hpp"
#include "Layout/ForceBasedLayout.hpp"
#include "Layout/BiCircularLayout.hpp"
#include "Layout/CircularLayout.hpp"
#include "Layout/BipartiteLayout.hpp"
#include "Layout/NCircularLayout.hpp"
#include "Layout/LinearLayout.hpp"
#include "Layout/TreeLayout.hpp"
#include "Layout/BinaryTreeLayout.hpp"
#include "Layout/GridLayout.hpp"
#include <QtDisplay/LayoutPainter.hpp>
namespace spider
{
    typedef GraphValue::Graph GT;
    Value* win_display(std::vector<Value*> args)
    {
        assert_size(args, 1);
        assert_type(args[0], VType::Graph);
        auto g = dynamic_cast<GraphValue*>(args[0]);
        return new WindowValue(g, new CircularLayout(*g));
    }
    
    Value* win_change_layout(std::vector<Value*> args)
    {
        assert_size(args, greater_eq(2));
        assert_type(args[0], VType::Window);
        assert_type(args[1], VType::String);
        WindowValue* win = getw(args[0]);
        std::string name = gets(args[1])->data;
        
        Layout* l;
        auto& g = *(win->data->getGraph());
        if (name == "circular")
            l = new CircularLayout(g);
        else if (name == "random")
            l = new RandomLayout(g);
        else if (name == "force")
            l = new ForceBasedLayout(g);
        else if (name == "bicircular")
        {
            float r = 0.5, c = 0.5;
            if (args.size() >=3)
            {
                assert_type(args[2], VType::Float);
                c = getf(args[2])->data;
            }
            if (args.size() == 4)
            {
                assert_type(args[3], VType::Float);
                r = getf(args[3])->data;
            }
            l = new BiCircularLayout(g, c, r);
        }
        else if (name == "wheel")
        {
            l = new BiCircularLayout(g, 1.0/ g.data->order(), 0);
        }
        else if(name == "tree")
        {
            assert_size(args,3);
            assert_type(args[2],VType::Integer);
            auto v = geti(args[2])->data;
            l = new TreeLayout(g, v);
        }
        else if(name == "binary_tree")
        {
            assert_size(args,3);
            assert_type(args[2],VType::Integer);
            auto v = geti(args[2])->data;
            l = new BinaryTreeLayout(g, v);
        }
        else if(name == "ncircular")
        {
            assert_size(args,3);
            assert_type(args[2],VType::Integer);
            auto n = geti(args[2])->data;
            l = new NCircularLayout(g, n);
        }
        else if(name == "linear")
        {
            auto isVertical = false;
            if(args.size() == 3)
            {
                assert_type(args[2],VType::Bool);
                isVertical = getb(args[2])->data;
            }
            l = new LinearLayout(g, isVertical);
        }
        else if(name == "grid")
        {
            auto isCol = true;
            assert_type(args[2],VType::Integer);
            auto n = geti(args[2])->data;
            if(args.size() == 4)
            {
                assert_type(args[3],VType::Bool);
                isCol = geti(args[2])->data;
            }
            l = new GridLayout(g, n, isCol);
        }
        else if (name == "bipartite")
        {
            float fraction = 0.5; 
            bool isVertical = true;
            if (args.size() >=3)
            {
                assert_type(args[2], VType::Float);
                fraction = getf(args[2])->data;
            }
            if (args.size() == 4)
            {
                assert_type(args[3], VType::Bool);
                isVertical = getb(args[3])->data;
            }
            l = new BipartiteLayout(g, fraction, isVertical);
        }
        
        else throw std::runtime_error("Layout: '" + name + "' not found.\n");
        
        win->data->changeLayout(l);
        return win;
    }
//     bool& displayText(){return op_displayText;}
//     bool& displayEdgeCost(){return op_displayEdgeCost;}
//     bool& useGradient(){return op_useGradient;}
//     bool& useVertexColorAttrib(){return op_useVertexColorAttrib;}
//     bool& useVertexColoring(){return op_vertexColoring;}
//     bool& useEdgeColoring(){return op_edgeColoring;}
    
    Value* win_display_vertex_name(std::vector<Value*> args)
    {
        assert_size(args, 2);
        assert_type(args[0], VType::Window);
        assert_type(args[1], VType::Bool);
        auto win = getw(args[0]);
        auto b = getb(args[1]);
        win->data->getLayoutPainter()->setDisplayText(b->data);
        win->data->changeCallback();
        return win;
    }
    Value* win_display_edge_cost(std::vector<Value*> args)
    {
        assert_size(args, 2);
        assert_type(args[0], VType::Window);
        assert_type(args[1], VType::Bool);
        auto win = getw(args[0]);
        auto b = getb(args[1]);
        win->data->getLayoutPainter()->setDisplayEdgeCost(b->data);
        win->data->changeCallback();
        return win;
    }
    Value* win_display_gradient(std::vector<Value*> args)
    {
        assert_size(args, 2);
        assert_type(args[0], VType::Window);
        assert_type(args[1], VType::Bool);
        auto win = getw(args[0]);
        auto b = getb(args[1]);
        win->data->getLayoutPainter()->setUseGradient(b->data);
        win->data->changeCallback();
        return win;
    }
    Value* win_display_vertex_coloring(std::vector<Value*> args)
    {
        assert_size(args, 2);
        assert_type(args[0], VType::Window);
        assert_type(args[1], VType::Bool);
        auto win = getw(args[0]);
        auto b = getb(args[1]);
        win->data->getLayoutPainter()->setVertexColoring(b->data);
        win->data->changeCallback();
        return win;
    }
    Value* win_display_edge_coloring(std::vector<Value*> args)
    {
        assert_size(args, 2);
        assert_type(args[0], VType::Window);
        assert_type(args[1], VType::Bool);
        auto win = getw(args[0]);
        auto b = getb(args[1]);
        win->data->getLayoutPainter()->setEdgeColoring(b->data);
        win->data->changeCallback();
        return win;
    }
    Value* win_mark_vertex(std::vector<Value*> args)
    {
        assert_size(args, 3);
        assert_type(args[0], VType::Window);
        assert_type(args[1], VType::Integer);
        assert_type(args[2], VType::String);
        
        auto win = getw(args[0]);
        auto v = geti(args[1]);
        auto s = gets(args[2]);
        win->data->getLayoutPainter()->markVertex(v->data, s->data);
        win->data->changeCallback();
        return win;
    }
    Value* win_mark_vertex_v2(std::vector<Value*> args)
    {
        assert_size(args, 3);
        assert_type(args[0], VType::Window);
        assert_type(args[1], VType::String);
        assert_type(args[2], VType::Integer);
        
        
        auto win = getw(args[0]);
        auto v = geti(args[2]);
        auto s = gets(args[1]);
        win->data->getLayoutPainter()->markVertex(v->data, s->data);
        win->data->changeCallback();
        return win;
    }
    
    Value* win_mark_edge(std::vector<Value*> args)
    {
        assert_size(args, 4);
        assert_type(args[0], VType::Window);
        assert_type(args[1], VType::Integer);
        assert_type(args[2], VType::Integer);
        assert_type(args[3], VType::String);
        
        auto win = getw(args[0]);
        auto x = geti(args[1]);
        auto y = geti(args[2]);
        auto s = gets(args[3]);
        win->data->getLayoutPainter()->markEdge(x->data, y->data , s->data);
        win->data->changeCallback();
        return win;
    }
    Value* win_mark_edge_v2(std::vector<Value*> args)
    {
        assert_size(args, 4);
        assert_type(args[0], VType::Window);
        assert_type(args[1], VType::String);
        assert_type(args[2], VType::List);
                
        auto win = getw(args[0]);
        auto x = geti(getl(args[2])->data[0]);
        auto y = geti(getl(args[2])->data[1]);
        auto s = gets(args[1]);
        win->data->getLayoutPainter()->markEdge(x->data, y->data , s->data);
        win->data->changeCallback();
        return win;
    }
}