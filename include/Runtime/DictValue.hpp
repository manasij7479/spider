#ifndef SPIDER_RUNTIME_DICT_VALUE_HPP
#define SPIDER_RUNTIME_DICT_VALUE_HPP
#include "Runtime/Type.hpp"
namespace spider
{
    class DictValue : public Value
    {
    public:
        DictValue(std::map<std::string, Value*> map) : Value(VType::Dict), data(map){}
        DictValue():Value(VType::Dict){}
        std::string show()
        {
            std::string result = "";
            for(auto v : data)
                result += (v.first+" : "+v.second->show() + " ");
            return result;
        }
        std::map<std::string, Value*> data;
    };
}
#endif