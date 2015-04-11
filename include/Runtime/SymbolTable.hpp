#ifndef SPIDER_RUNTIME_SYMBOL_TABLE_HPP
#define SPIDER_RUNTIME_SYMBOL_TABLE_HPP
#include <map>
#include <vector>
#include "Runtime/Type.hpp"
/**
 * \brief - to store a map of user defined identifiers.
 * **/
namespace spider
{
    /**
     * \brief - Class to implement symbol table containing names and values of user defined identifiers.
     * **/
    class SymbolTable
    {
        typedef std::map<std::string, Value*> Map;
    public:
        SymbolTable()///<Constructor
        {
            push();
        }
        /**
	 * \brief - to push new variable scope to the stack.
	 * **/
        void push(){stack.push_back(Map());}
        /**
	 * \brief - to obtain the latest variable scope from stack top.
	 * **/
        void pop(){stack.pop_back();} //cleanup?
        /**
	 * \brief - to modify the value of an identifier
	 * 
	 * @param std::string name - First Parameter, name of the identifier whose value is to be changed.
	 * 
	 * @param Value* x - Second Parameter, new value for the identifier.
	 * **/
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
        /**
	 * \brief - to insert value for an identifier present in the latest scope at top of stack.
	 * 
	 * @param std::string name - First Parameter, name of the identifier whose value is to be inserted.
	 * 
	 * @param Value* x - Second Parameter, value for the identifier.
	 * **/
        void insert(std::string name, Value* x)
        {
            stack.back()[name] = x;
        }
        /**
	 * \brief - to return the value of an identifier from any scope present in the stack
	 * 
	 * @param std::string name - Parameter, name of the identifier.
	 * 
	 * @returns Value* - value of an identifier.
	 * **/
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
        /**
	 * \brief - to return the value of an identifier from the latest scope present at the top of the stack.
	 * 
	 * @param std::string name - Parameter, name of the identifier.
	 * 
	 * @returns Value* - value of an identifier.
	 * **/
        Value* local_get(std::string name)
        {
            auto it = stack[stack.size()-1].find(name);
            if(it != stack[stack.size()-1].end())
                return it->second;
            return nullptr;
        }
        /**
	 * \brief - function to clear the stack.
	 * **/
        void clear()
        {
            stack.clear();
        }
    private:
        std::vector<Map> stack;
    };
}
#endif
