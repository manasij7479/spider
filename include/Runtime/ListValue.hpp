#ifndef SPIDER_RUNTIME_LIST_VALUE_HPP
#define SPIDER_RUNTIME_LIST_VALUE_HPP
#include "Runtime/Type.hpp"
namespace spider
{
    class ListValue : public Value
    {
    public:
        ListValue(std::vector<Value*> li) : Value(VType::List), data(li){}
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