#include "Runtime/Type.hpp"
#include <vector>
namespace spider
{
    Value* int_add(std::vector<Value*> args)
    {
        int result = 0;
        for (auto i : args)
        {
            assert_type(i, VType::Integer);
            auto iv = geti(i);
            result += iv->data;
        }
        return new IntegerValue(result);
    }
    Value* bool_or(std::vector<Value*> args)
    {
        bool result = false;
        for (auto i : args)
        {
            assert_type(i, VType::Bool);
            result = result || getb(i)->data;
        }
        return new BoolValue(result);
    }
    Value* bool_and(std::vector<Value*> args)
    {
        bool result = true;
        for (auto i : args)
        {
            assert_type(i, VType::Bool);
            result = result && getb(i)->data;
        }
        return new BoolValue(result);
    }
    
    Value* bool_not(std::vector<Value*> args)
    {
        assert_size(args, 1);
        assert_type(args[0], VType::Bool);
        return new BoolValue(!(getb(args[0])->data));
    }
    
}