#ifndef SYMBOL_TABLE_HPP
#define SYMBOL_TABLE_HPP
#include <map>
#include <iostream>
#include "Types.hpp"
namespace spc
{
    class SymbolTable
    {
    public:
        SymbolTable(){push();}
        void push(){data.push_back(Scope());}
        void pop(){data.pop_back();}
        std::pair<bool, Type> lookup(std::string name)
        {
            for (int i = data.size()-1; i >=0; --i)
            {
                auto p = data[i].lookup(name);
                if (p.first == true)
                    return p;
            }
            return {false, Type()};
        }
        std::pair<bool, Type> lookupLocal(std::string name) 
        {
            return data.back().lookup(name);
        }
        std::string getNewName(Type t)
        {
            return data.back().getNewName(t);
        }
        void insert(std::string name, Type t)
        {
//             std::cerr<<"INS:"<<name<<std::endl;
            data.back().map[name] = t;
            //What if name is already there ?
            //Handle this case when calling, maybe.
        }
    private:
        struct Scope
        {
            Scope():counter(0){};
            std::map<std::string, Type> map;
            int counter;
            std::string getNewName(Type t)
            {
                std::string newname;
                do
                {
                    newname = "t" + std::to_string(counter++);
                }
                while(map.find(newname) != map.end());
                map[newname] = t;
                return newname;
            }
            std::pair<bool, Type> lookup(std::string name)
            {
                auto it = map.find(name);
                if (it == map.end())
                    return {false, Type()};
                else return {true, it->second};
            }
        };
        std::vector<Scope> data;
        
    };
}
#endif