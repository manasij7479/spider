#ifndef SPIDER_RUNTIME_FUNCTION_HPP
#define SPIDER_RUNTIME_FUNCTION_HPP
#include <functional>
#include <map>
#include <vector>
#include "Type.hpp"
namespace spider
{
    typedef std::function<Value*(std::vector<Value*>)> Function;
    extern std::map<std::string, Function> FunctionMap;

}
#endif