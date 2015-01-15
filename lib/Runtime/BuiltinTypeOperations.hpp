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
    
<<<<<<< HEAD
    Value* float_add(std::vector<Value*> args)
    {
        int result = 0;
        for (auto i : args)
        {
            assert_type(i, VType::Float);
            auto iv = getf(i);
            result += iv->data;
        }
        return new FloatValue(result);
    }
    
    Value* float_greater(std::vector<Value*> args)
    {
        assert_size(args, 2);
        assert_type(args[0], VType::Float);
        assert_type(args[1], VType::Float);
        return new BoolValue(getf(args[0])->data > getf(args[1])->data);
    }
    Value* float_lesser(std::vector<Value*> args)
    {
        assert_size(args, 2);
        assert_type(args[0], VType::Float);
        assert_type(args[1], VType::Float);
        return new BoolValue(getf(args[0])->data < getf(args[1])->data);
    }
    Value* float_equal(std::vector<Value*> args)
    {
        assert_size(args, 2);
        assert_type(args[0], VType::Float);
        assert_type(args[1], VType::Float);
        return new BoolValue(getf(args[0])->data == getf(args[1])->data);
    }
    
=======
>>>>>>> beb8bf0b9ff1c64311a36b49fb379234593473a0
}
