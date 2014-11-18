#ifndef SPIDER_USER_FUNCTION_MAPS
#define SPIDER_USER_FUNCTION_MAPS
#include <unordered_map>
#include <functional>
#include "UserEnv/UserTypes.hpp"
#include "UserEnv/UserFunctions.hpp"
namespace spider
{
    namespace user
    {
        std::unordered_map<std::string, std::function<void()>> vvMap = 
        {
            {"testFunction", testFunction}
        };
    }
}
#endif