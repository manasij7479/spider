#include "NewRuntime/WindowValue.hpp"
namespace spider
{
    Value* make_window(std::vector<Value*> args)
    {
        assert_size(args, 1);
        assert_type(args[0], VType::Graph);
        auto g = dynamic_cast<GraphValue*>(args[0]);
//             std::cerr<<"FOO:"<<(g == nullptr)<<"\n";
//             std::cerr << g->data->order();
//             std::cerr<<"\nBAR\n";
        return new WindowValue(g);
    }
}