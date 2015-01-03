#ifndef SPIDER_RUNTIME_HPP
#define SPIDER_RUNTIME_HPP
#include "Runtime/UserGraph.hpp"
#include "Runtime/UserWindow.hpp"
#include <map>
#include <vector>
#include <string>
#include <stdexcept>
namespace spider
{
    class Runtime
    {
    public:
        Runtime(spider::EventManager* eMgr):eventManager(eMgr){};
        void eval(std::vector<std::string> args)
        {
            if (args[0] == "create")
            {
                if (args.size() < 3)
                    throw std::runtime_error("Expected more arguments");
                std::string type = args[1];
                std::string name = args[2];
                std::string exists = getType(name);
                if (exists != "none")
                    throw std::runtime_error("Name" + name + 
                                            "exists as" + exists);
                if (type == "graph")
                {
                    args.erase(args.begin());
                    args.erase(args.begin());
                    args.erase(args.begin());
                    graphMap[name] = new UserGraph(args);
//                     std::cout << "Graph " << name << " created."<<std::endl;
                }
                else if (type == "window")
                {
                    args.erase(args.begin());
                    args.erase(args.begin());
                    args.erase(args.begin());
                    UserGraph* g = graphMap[args[0]];
                    //TODO: Handle errors
                    args.erase(args.begin());
                    UserWindow* win = new UserWindow(g,eventManager, args);
                    windowMap[name] = win;
                }
               
            }
            //other keywords go here in else if blocks
            else
            {
                std::string type = getType(args[0]);
                if (type == "graph")
                {
                    std::string name = args[0];
                    args.erase(args.begin());
                    graphMap[name]->eval(args);
                }
                else if (type == "window")
                {
                    std::string name = args[0];
                    args.erase(args.begin());
                    windowMap[name]->eval(args);
                }
            }
            
        }
        std::string getType(std::string name) //TODO: Maybe use enums instead of strings if this ever becomes a bottleneck
        {
            if (name == "create")
                return "keyword";
            if (graphMap.find(name)!=graphMap.end())
                return "graph";
            if (windowMap.find(name)!=windowMap.end())
                return "window";
            return "none";
        }
        UserGraph& getGraph(std::string name)
        {
            //TODO handle `not found` error
            return *graphMap[name];
        }
        UserWindow& getWindow(std::string name)
        {            
            //TODO handle `not found` error
            return *windowMap[name];
        }
    private:
        std::map<std::string, spider::UserGraph*> graphMap;
        std::map<std::string, spider::UserWindow*> windowMap;
        spider::EventManager* eventManager;
    };
}
#endif