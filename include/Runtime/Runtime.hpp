#ifndef SPIDER_RUNTIME_HPP
#define SPIDER_RUNTIME_HPP
#include "Runtime/UserGraph.hpp"
#include "Runtime/UserWindow.hpp"
#include "Runtime/Context.hpp"
#include <map>
#include <vector>
#include <string>
#include <stdexcept>

namespace spider
{
    class Runtime
    {
    public:
        void eval(std::vector<std::string> args)
        {
            if (args[0] == "create")
            {
                if (args.size() < 3)
                    throw std::runtime_error("Expected more arguments");
                std::string type = args[1];
                std::string name = args[2];
                
                if (type == "graph")
                {
                    args.erase(args.begin());
                    args.erase(args.begin());
                    args.erase(args.begin());
                    context.insertGraph(name, new UserGraph(args));
//                     std::cout << "Graph " << name << " created."<<std::endl;
                }
                else if (type == "window")
                {
                    args.erase(args.begin());
                    args.erase(args.begin());
                    args.erase(args.begin());
                    UserGraph* g = context.getGraph(args[0]);
                    //TODO: Handle errors
                    args.erase(args.begin());
                    UserWindow* win = new UserWindow(g, args);
                    context.insertWindow(name,win);
                }
               
            }
            //other keywords go here in else if blocks
            else
            {
                std::string type = context.getType(args[0]);
                if (type == "graph")
                {
                    std::string name = args[0];
                    args.erase(args.begin());
                    context.getGraph(name)->eval(args);
                }
                else if (type == "window")
                {
                    std::string name = args[0];
                    args.erase(args.begin());
                    context.getWindow(name)->eval(args);
                }
            }
            
        }

    private:
        Context context;
    };
}
#endif