#ifndef SPIDER_RUNTIME_USER_FUNCTION_HPP
#define SPIDER_RUNTIME_USER_FUNCTION_HPP
#include <vector>
#include <string>
#include "Runtime/Type.hpp"

namespace spider
{
    class Statement;
    class UserFunction
    {
    public:
        UserFunction(std::vector<std::string> proto, Statement* block_);
        Value* call(std::vector<Value*> args);
    private:
        std::string name;
        Statement* block;
        std::vector<std::pair<std::string, VType>> formal_params;
        std::pair<std::string, VType> return_idf;
    };
}
#endif