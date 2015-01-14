#include "NewRuntime/Functions.hpp"
#include "BuiltinTypeOperations.hpp"
namespace spider
{
    std::map<std::string, Function> FunctionMap = 
    {
        {"add_int", add_int}
    };
}