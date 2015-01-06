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
        
        void insertGraph(std::string name, UserGraph* g)
        {
            top().insertGraph(name, g);
        }
        void insertWindow(std::string name, UserWindow* win)
        {
            top().insertWindow(name, win);
        }
        void insertInt(std::string name, UserInt* i)
        {
            top().insertInt(name, i);
        }
        
        std::pair<std::string,int> locate(std::string name)
        {
            for(int i = stack.size()-1; i >=0; --i)
            {
                std::string type = stack[i]->getType(name);
                if(type != "none")
                    return {type, i};
            }
            return {"none", -1};
        }
        std::string getType(std::string name)
        {
            return locate(name).first;
        }
        UserGraph* getGraph(std::string name)
        {
            auto location = locate(name);
            if (location.first == "none")
                return nullptr;
            else return stack[location.second]->getGraph(name);
        }
        UserWindow* getWindow(std::string name)
        {            
            auto location = locate(name);
            if (location.first == "none")
                return nullptr;
            else return stack[location.second]->getWindow(name);
        }
        UserInt* getInt(std::string name)
        {            
            auto location = locate(name);
            if (location.first == "none")
                return nullptr;
            else return stack[location.second]->getInt(name);
        }
    private:
        std::vector<spider::Context*> stack;
    };
}
#endif