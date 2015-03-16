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
    Value* list_create_list(std::vector<Value*> args)
    {
        return convertToValue(args);
    }
    Value* list_value_at(std::vector<Value*> args)
    {
        assert_size(args, 2);
        assert_type(args[0], VType::List);
        assert_type(args[1], VType::Integer);
        
        auto& ldata  = getl(args[0])->data;
        int i = geti(args[1])->data;
        assert_size(ldata, greater(i), "List index out of bounds");
        return ldata[i];
    }
}
 