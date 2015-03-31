#include "Runtime/FunctionValue.hpp"
#include "Runtime/Runtime.hpp"
#include "Runtime/TypeOps.hpp"
namespace spider
{
    FunctionValue::FunctionValue(std::vector<std::string> proto, Statement* block_)
    {
        block = block_;
        assert_size(proto, greater_eq(4));// function keyword, name, return var, return
        assert_size(proto, [](int i){return i%2 == 0;}); // must be even
        name = proto[1];
        
        auto&& n_t_map =  Value::NameToTypeMap();
        
        return_idf = {proto[2],n_t_map[proto[3]]};
        for (uint i = 4; i < proto.size(); i+=2)
            formal_params.push_back({proto[i], n_t_map[proto[i+1]]});
    }
    Value* FunctionValue::call(std::vector<Value*> args, FunctionSystem& f, SymbolTable& table)
    {
        assert_size(args, formal_params.size());
        table.push();
        for(uint i = 0; i < args.size(); ++i)
        {
            assert_type(args[i], formal_params[i].second);
            table.insert(formal_params[i].first, args[i]);
        }
        Runtime nested(table, f, true);
        nested.eval(*block);
        Value* result = nested.getFromSymbolTable(return_idf.first);
        if (result == nullptr)
            throw std::runtime_error("Null return.\n");
        assert_type(result, return_idf.second);
//         std::cout << result->show() <<std::endl;
        table.pop();
        return result;
    }
}