#include "Runtime/WindowValue.hpp"
#include "Runtime/TypeOps.hpp"
#include "Layout/ForceBasedLayout.hpp"
#include "Layout/BiCircularLayout.hpp"
#include "Layout/CircularLayout.hpp"
#include "Layout/BipartiteLayout.hpp"
#include "Layout/NCircularLayout.hpp"
#include "Layout/LinearLayout.hpp"
#include "Layout/TreeLayout.hpp"
#include "Layout/GridLayout.hpp"
namespace spider
{
    typedef GraphValue::Graph GT;
    Value* win_display(std::vector<Value*> args)
    {
        assert_size(args, 1);
        assert_type(args[0], VType::Graph);
        auto g = dynamic_cast<GraphValue*>(args[0]);
        return new WindowValue(g, new CircularLayout<GT>(*(g->data)));
    }
    
    Value* win_change_layout(std::vector<Value*> args)
    {
        assert_size(args, greater_eq(2));
        assert_type(args[0], VType::Window);
        assert_type(args[1], VType::String);
        WindowValue* win = getw(args[0]);
        std::string name = gets(args[1])->data;
        
        Layout<GT>* l;
        auto& g = *(win->data->getGraph()->data);
        if (name == "circular")
            l = new CircularLayout<GT>(g);
        else if (name == "random")
            l = new RandomLayout<GT>(g);
        else if (name == "force")
            l = new ForceBasedLayout<GT>(g);
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
            l = new BiCircularLayout<GT>(g, c, r);
        }
        else if (name == "wheel")
        {
            l = new BiCircularLayout<GT>(g, 1.0/ g.order(), 0);
        }
        else if(name == "tree")
        {
            assert_size(args,3);
            assert_type(args[2],VType::Integer);
            auto v = geti(args[2])->data;
            l = new TreeLayout<GT>(g, v);
        }
        else throw std::runtime_error("Layout: '" + name + "' not found.\n");
        
        win->data->changeLayout(l);
        return win;
    }
}