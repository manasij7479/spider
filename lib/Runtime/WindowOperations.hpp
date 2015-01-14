#include "Runtime/WindowValue.hpp"
#include "Runtime/TypeOps.hpp"
#include "Layout/ForceBasedLayout.hpp"
namespace spider
{
    Value* make_win(std::vector<Value*> args)
    {
        assert_size(args, 1);
        assert_type(args[0], VType::Graph);
        auto g = dynamic_cast<GraphValue*>(args[0]);
        return new WindowValue(g);
    }
    typedef GraphValue::Graph GT;
    Value* change_layout(std::vector<Value*> args)
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
        else throw std::runtime_error("Layout: '" + name + "' not found.\n");
        
        win->data->setLayout(l);
        return win;
    }
}