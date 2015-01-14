#include "NewRuntime/WindowValue.hpp"
namespace spider
{
    Value* make_win(std::vector<Value*> args)
    {
        assert_size(args, 1);
        assert_type(args[0], VType::Graph);
        auto g = dynamic_cast<GraphValue*>(args[0]);
        return new WindowValue(g);
    }
}