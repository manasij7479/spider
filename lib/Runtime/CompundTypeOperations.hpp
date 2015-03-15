#include "Runtime/ListValue.hpp"
#include "Runtime/DictValue.hpp"
#include "Runtime/TypeOps.hpp"
namespace spider
{
    Value* dict_create_dict(std::vector<Value*> args)
    {
        assert_size(args, [](int n){return n%2 == 0;});
        auto map = new DictValue();
        for(uint i = 0; i < args.size(); i += 2)
        {
            assert_type(args[i], VType::String);
            map->data[gets(args[i])->data] = args[i+1];
        }
        return map;
    }
}
 