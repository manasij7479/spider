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
    
    Value* list_map(std::vector<Value*> args)
    {
        assert_size(args, 2);
        assert_type(args[0], VType::List);
        assert_type(args[1], VType::Function);
        
        std::vector<Value*> result;
        auto l = getl(args[0]);
        auto f = getfn(args[1]);
        for (auto v : l->data)
            result.push_back(f->call({v}));
        return new ListValue(result);
    }
    Value* list_for_each(std::vector<Value*> args)
    {
        assert_size(args, 3);
        assert_type(args[0], VType::List);
        assert_type(args[1], VType::Function);
        assert_type(args[2], VType::List);
        std::vector<Value*> result;
        auto l = getl(args[0]);
        auto f = getfn(args[1]);
        auto callargs = getl(args[2]);
        for (auto v : l->data)
        {
            callargs->data.push_back(v);
            result.push_back(f->call(callargs->data));
            callargs->data.pop_back();
        }
        return new ListValue(result);
    }
    Value* list_size(std::vector<Value*> args)
    {
        assert_size(args, 1);
        assert_type(args[0], VType::List);
        return new IntegerValue(getl(args[0])->data.size());
    }
}
 