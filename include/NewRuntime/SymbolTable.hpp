#ifndef SPIDER_RUNTIME_SYMBOL_TABLE_HPP
#define SPIDER_RUNTIME_SYMBOL_TABLE_HPP
#include <map>
#include <vector>
#include "Type.hpp"
namespace spider
{
    class SymbolTable
    {
        typedef std::map<std::string, Value*> Map;
    public:
        void push(){stack.push_back(Map());}
        void pop(){stack.pop_back();} //cleanup?
        
        void insert(std::string name, Value* x)
        {
            stack.back()[name] = x;
        }
        Value* get(std::string name)
        {
            for(int i = stack.size()-1; i >=0; --i)
            {
                auto it = stack[i].find(name);
                if(it != stack[i].end())
                    return it->second;
            }
            return nullptr;
        }
    private:
        std::vector<Map> stack;
    };
}
#endif
