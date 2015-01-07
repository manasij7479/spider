#ifndef SPIDER_USER_STRING_HPP
#define SPIDER_USER_STRING_HPP
#include <Runtime/UserType.hpp>
#include <string>
#include <vector>
#include <iostream>
namespace spider
{
    class UserString : public UserType
    {
    public:
        UserString(std::vector<std::string> args) : UserType(UserType::Type::String)
        {
            data = args[0];
        }
        std::string get(){return data;}
        void eval(std::vector<std::string> args)
        {
            //TODO: ERROR checking
            if(args.empty())//maybe this should be an error
                return;
            if (args[0] == "show")
                std::cout<<data<<std::endl;
            //TODO: Add more ops, like cat 
        }
    private:
        std::string data;
    };
}
#endif