#ifndef SPIDER_RUNTIME_HPP
#define SPIDER_RUNTIME_HPP
#include "Runtime/UserGraph.hpp"
#include "Runtime/UserWindow.hpp"
#include "Runtime/ContextStack.hpp"
#include <map>
#include <vector>
#include <string>
#include <stdexcept>

namespace spider
{
    class Runtime
    {
    public:
        Runtime()
        {
            context.push();
        }
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
                    UserWindow* win = new UserWindow(g, args); //TODO: Give a ContextStack ptr to the objects to look values up on its own
                    context.insertWindow(name,win);
                }
                else if (type == "int")
                {
                    args.erase(args.begin());
                    args.erase(args.begin());
                    args.erase(args.begin());
                    context.insertInt(name, new UserInt(args));
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
                else if (type == "int")
                {
                    std::string name = args[0];
                    args.erase(args.begin());
                    context.getInt(name)->eval(args);
                }
                else if (type == "none")
                {
                    throw std::runtime_error("Non Existent Identifier: " + args[0]);
                }
                else
                {
                    std::cerr<<"UNSUPPORTED TYPE: "<< type <<std::endl;
                    
                }
            }
            
        }

    private:
        ContextStack context;
    };
}
#endif