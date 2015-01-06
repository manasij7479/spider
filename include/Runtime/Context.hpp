#ifndef SPIDER_RUNTIME_CONTEXT_HPP
#define SPIDER_RUNTIME_CONTEXT_HPP
#include "Runtime/UserGraph.hpp"
#include "Runtime/UserWindow.hpp"
#include "Runtime/UserInt.hpp"
#include <map>
namespace spider
{
    class Context
    {
    public:
        void insertGraph(std::string name, UserGraph* g)
        {
            if (getType(name) == "none")
                graphMap[name] = g;
            else throw std::runtime_error("Name already exists in Context.\n");
        }
        void insertInt(std::string name, UserInt* i)
        {
            if (getType(name) == "none")
                intMap[name] = i;
            else throw std::runtime_error("Name already exists in Context.\n");
        }
        
        void insertWindow(std::string name, UserWindow* win)
        {
            if (getType(name) == "none")
                windowMap[name] = win;
            else throw std::runtime_error("Name already exists in Context.\n");
        }
        std::string getType(std::string name) //TODO: Maybe use enums instead of strings if this ever becomes a bottleneck
        {
            if (graphMap.find(name)!= graphMap.end())
                return "graph";
            if (windowMap.find(name)!= windowMap.end())
                return "window";
            if (intMap.find(name)!= intMap.end())
                return "int";
            return "none";
        }
        UserGraph* getGraph(std::string name)
        {
            //TODO handle `not found` error
            return graphMap[name];
        }
        UserWindow* getWindow(std::string name)
        {            
            //TODO handle `not found` error
            return windowMap[name];
        }
        UserInt* getInt(std::string name)
        {
            return intMap[name];
        }
    private:
        std::map<std::string, spider::UserGraph*> graphMap;
        std::map<std::string, spider::UserWindow*> windowMap;
        std::map<std::string, spider::UserInt*> intMap;
    };
}
#endif