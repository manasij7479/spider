#ifndef SPIDER_RUNTIME_LIST_VALUE_HPP
#define SPIDER_RUNTIME_LIST_VALUE_HPP
#include "Runtime/Type.hpp"
#include "Runtime/TypeOps.hpp"
namespace spider
{
    class ListValue : public Value
    {
    public:
        template <typename T>
        ListValue(std::vector<T> li) : data(convertToValue(li)), Value(VType::List){}
        ListValue():Value(VType::List){}
        std::string show()
        {
            std::string result = "";
            for(auto v : data)
                result += (v->show() + " ");
            return result;
        }
        std::vector<Value*> data;
    };
}
#endif