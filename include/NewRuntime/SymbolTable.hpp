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
        SymbolTable()
        {
            push();
        }
        void push(){stack.push_back(Map());}
        void pop(){stack.pop_back();} //cleanup?
        void modify(std::string name, Value* x)
        {
            for(int i = stack.size()-1; i >=0; --i)
            {
                if (stack[i].find(name) != stack[i].end())
                {
                    stack[i][name] = x;
                    break;
                }
                    
            }
        }
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
