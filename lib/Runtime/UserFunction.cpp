#include "Runtime/UserFunction.hpp"
#include "Runtime/Runtime.hpp"
#include "Runtime/TypeOps.hpp"
namespace spider
{
    UserFunction::UserFunction(std::vector<std::string> proto, Statement* block_)
    {
        block = block_;
        assert_size(proto, greater_eq(4));// function keyword, name, return var, return
        assert_size(proto, [](int i){return i%2 == 0;}); // must be even
        name = proto[1];
        
        auto&& n_t_map =  Value::NameToTypeMap();
        
        return_idf = {proto[2],n_t_map[proto[3]]};
        for (int i = 4; i < proto.size(); i+=2)
            formal_params.push_back({proto[i], n_t_map[proto[i+1]]});
    }
    Value* UserFunction::call(std::vector<Value*> args)
    {
        assert_size(args, formal_params.size());
        SymbolTable context;
        for(int i = 0; i < args.size(); ++i)
        {
            assert_type(args[i], formal_params[i].second);
            context.insert(formal_params[i].first, args[i]);
        }
        Runtime nested(context);
        nested.eval(*block);
        auto result = nested.getFromSymbolTable(return_idf.first);
        assert_type(result, return_idf.second);
        return result;
    }
}