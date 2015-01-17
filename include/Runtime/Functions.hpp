#ifndef SPIDER_RUNTIME_FUNCTION_HPP
#define SPIDER_RUNTIME_FUNCTION_HPP
#include <functional>
#include <map>
#include <vector>
#include "Runtime/Type.hpp"
namespace spider
{
    
    class FunctionSystem
    {
        typedef std::function<Value*(std::vector<Value*>)> Function;
    public:
        FunctionSystem();
        bool isFunction(std::string name)
        {
            return FunctionMap.find(name) != FunctionMap.end();
        }
        Function& get(std::string name)
        {
            if (isFunction(name))
                return FunctionMap[name];
        }
    private:
        std::map<std::string, Function> FunctionMap;
    };

}
#endif