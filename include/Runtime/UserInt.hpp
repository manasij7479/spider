#ifndef SPIDER_USER_INT_HPP
#define SPIDER_USER_INT_HPP
#include <string>
#include <vector>
#include <iostream>
namespace spider
{
    class UserInt
    {
    public:
        UserInt(std::vector<std::string> args){data = std::stoi(args[0]);}
        int get(){return data;}
        void eval(std::vector<std::string> args)
        {
            //TODO: ERROR checking
            if(args.empty())//maybe this should be an error
                return;
            if (args[0] == "show")
                std::cout<<data<<std::endl;
            else if (args[0] == "set")
            {
                data = std::stoi(args[1]);
            }
            else if (args[0] == "add")
            {
                data += std::stoi(args[1]);
            }
            else if (args[0] == "sub")
            {
                data -= std::stoi(args[1]);
            }
            else if (args[0] == "mul")
            {
                data *= std::stoi(args[1]);
            }
            else if (args[0] == "div")
            {
                data /= std::stoi(args[1]);
            }
        }
    private:
        int data;
    };
}
#endif