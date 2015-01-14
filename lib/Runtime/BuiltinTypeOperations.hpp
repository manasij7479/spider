#include "Runtime/Type.hpp"
#include <vector>
namespace spider
{
    Value* add_int(std::vector<Value*> args)
    {
        int result = 0;
        for (auto i : args)
        {
            assert_type(i, VType::Integer);
            IntegerValue* iv = static_cast<IntegerValue*>(i);
            result += iv->data;
        }
        return new IntegerValue(result);
    }
}