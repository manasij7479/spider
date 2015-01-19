#include "Runtime/Type.hpp"
#include "Runtime/TypeOps.hpp"
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
    Value* int_sub(std::vector<Value*> args)
    {
        assert_type(args[0], VType::Integer);
        assert_type(args[1], VType::Integer);
        return new IntegerValue(geti(args[0])->data - geti(args[1])->data);
    }
    Value* int_div(std::vector<Value*> args)
    {
        assert_type(args[0], VType::Integer);
        assert_type(args[1], VType::Integer);
        return new IntegerValue(geti(args[0])->data / geti(args[1])->data);
    }
    Value* int_mul(std::vector<Value*> args)
    {
        assert_type(args[0], VType::Integer);
        assert_type(args[1], VType::Integer);
        return new IntegerValue(geti(args[0])->data * geti(args[1])->data);
    }
    Value* int_mod(std::vector<Value*> args)
    {
        assert_type(args[0], VType::Integer);
        assert_type(args[1], VType::Integer);
        return new IntegerValue(geti(args[0])->data % geti(args[1])->data);
    }
    Value* int_greater(std::vector<Value*> args)
    {
        assert_size(args, 2);
        assert_type(args[0], VType::Integer);
        assert_type(args[1], VType::Integer);
        return new BoolValue(geti(args[0])->data > geti(args[1])->data);
    }
    Value* int_lesser(std::vector<Value*> args)
    {
        assert_size(args, 2);
        assert_type(args[0], VType::Integer);
        assert_type(args[1], VType::Integer);
        return new BoolValue(geti(args[0])->data < geti(args[1])->data);
    }
    Value* int_equal(std::vector<Value*> args)
    {
        assert_size(args, 2);
        assert_type(args[0], VType::Integer);
        assert_type(args[1], VType::Integer);
        return new BoolValue(geti(args[0])->data == geti(args[1])->data);
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

    Value* float_addf(std::vector<Value*> args)
    {
        float result = 0;
        for (auto i : args)
        {
            assert_type(i, VType::Float);
            auto iv = getf(i);
            result += iv->data;
        }
        return new FloatValue(result);
    }
    
    Value* float_greaterf(std::vector<Value*> args)
    {
        assert_size(args, 2);
        assert_type(args[0], VType::Float);
        assert_type(args[1], VType::Float);
        return new BoolValue(getf(args[0])->data > getf(args[1])->data);
    }
    Value* float_lesserf(std::vector<Value*> args)
    {
        assert_size(args, 2);
        assert_type(args[0], VType::Float);
        assert_type(args[1], VType::Float);
        return new BoolValue(getf(args[0])->data < getf(args[1])->data);
    }
    Value* float_equalf(std::vector<Value*> args)
    {
        assert_size(args, 2);
        assert_type(args[0], VType::Float);
        assert_type(args[1], VType::Float);
        return new BoolValue(getf(args[0])->data == getf(args[1])->data);
    }
    Value* float_subf(std::vector<Value*> args)
    {
        assert_type(args[0], VType::Float);
        assert_type(args[1], VType::Float);
        return new FloatValue(getf(args[0])->data - getf(args[1])->data);
    }
    Value* float_mulf(std::vector<Value*> args)
    {
        assert_type(args[0], VType::Float);
        assert_type(args[1], VType::Float);
        return new FloatValue(getf(args[0])->data * getf(args[1])->data);
    }
    Value* float_divf(std::vector<Value*> args)
    {
        assert_type(args[0], VType::Float);
        assert_type(args[1], VType::Float);
        return new FloatValue(getf(args[0])->data / getf(args[1])->data);
    }
}
