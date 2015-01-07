#ifndef SPIDER_RUNTIME_HPP
#define SPIDER_RUNTIME_HPP
#include "Runtime/UserGraph.hpp"
#include "Runtime/UserWindow.hpp"
#include "Runtime/UserInt.hpp"
#include "Runtime/UserString.hpp"
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
                    context.insert(name, new UserGraph(args));
//                     std::cout << "Graph " << name << " created."<<std::endl;
                }
                else if (type == "window")
                {
                    args.erase(args.begin());
                    args.erase(args.begin());
                    args.erase(args.begin());
                    auto g = static_cast<UserGraph*>(context.get(args[0]));
                    //TODO: Handle errors
                    args.erase(args.begin());
                    UserWindow* win = new UserWindow(g, args); //TODO: Give a ContextStack ptr to the objects to look values up on its own
                    context.insert(name,win);
                }
                else if (type == "int")
                {
                    args.erase(args.begin());
                    args.erase(args.begin());
                    args.erase(args.begin());
                    context.insert(name, new UserInt(args));
                }
                else if (type == "string")
                {
                    args.erase(args.begin());
                    args.erase(args.begin());
                    args.erase(args.begin());
                    context.insert(name, new UserString(args));
                }
               
            }
            //other keywords go here in else if blocks
            else
            {
                UserType* obj = context.get(args[0]);
                if (obj == nullptr)
                    throw std::runtime_error("Non Existent Identifier: " + args[0]);
                if (obj->type == UserType::Type::Graph)
                {
                    std::string name = args[0];
                    args.erase(args.begin());
                    static_cast<UserGraph*>(obj)->eval(args);
                }
                else if (obj->type == UserType::Type::Window)
                {
                    std::string name = args[0];
                    args.erase(args.begin());
                    static_cast<UserWindow*>(obj)->eval(args);
                }
                else if (obj->type == UserType::Type::Int)
                {
                    std::string name = args[0];
                    args.erase(args.begin());
                    static_cast<UserInt*>(obj)->eval(args);
                }
                else if (obj->type == UserType::Type::String)
                {
                    std::string name = args[0];
                    args.erase(args.begin());
                    static_cast<UserString*>(obj)->eval(args);
                }
                else
                {
                    std::cerr<<"UNSUPPORTED TYPE"<<std::endl;
                    
                }
            }
            
        }

    private:
        ContextStack context;
    };
}
#endif