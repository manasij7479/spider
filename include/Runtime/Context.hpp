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
        void insert(std::string name, UserType* obj)
        {
            if (table.find(name) == table.end())
                table[name] = obj;
           else throw std::runtime_error("Name already exists in Context.\n");
        }
        UserType* get(std::string name)
        {
            auto it = table.find(name);
            if (it == table.end())
                return nullptr;
            else return table[name];
        }
        bool exists(std::string name)
        {
            return table.find(name) != table.end();
        }
        UserType::Type getType(std::string name)
        {
            auto obj = get(name);
            if (obj != nullptr)
                return obj->type;
            return UserType::Type::NONE;
        }
    private:
        std::map<std::string, spider::UserType*> table;
    };
}
#endif