#ifndef SPIDER_CONTEXT_STACK_HPP
#define SPIDER_CONTEXT_STACK_HPP
#include <vector>
#include <Runtime/Context.hpp>
namespace spider
{
    class ContextStack
    {
    public:
        
        void push()
        {
            stack.push_back(new Context());
        }
        void pop()
        {
            stack.pop_back(); //TODO: maybe some cleanup needed
        }
        Context& top()
        {
            return *stack.back();
        }
        
        void insert(std::string name, UserType* obj)
        {
            top().insert(name, obj);
        }
        
        int locate(std::string name)
        {
            for(int i = stack.size()-1; i >= 0 ; --i)
            {
                if(stack[i]->exists(name))
                    return i;
            }
            return -1;
        }
        UserType* get(std::string name)
        {
            auto location = locate(name);
            if (location == -1)
                return nullptr;
            else return stack[location]->get(name);
        }
    private:
        std::vector<spider::Context*> stack;
    };
}
#endif