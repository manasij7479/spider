#ifndef SPIDER_RESOURCE_BUCKET_HPP
#define SPIDER_RESOURCE_BUCKET_HPP
#include "Resource/Resource.hpp"
#include <map>
namespace spider
{
    class ResourceBucket // Stores Resources of the same type
    {
    public:
        Resource* get(unsigned long id)
        {
            auto it = data.find(id);
            if (it == data.end())
                return nullptr;
            else return it->second;
        }
        void set(unsigned long id, Resource* res)
        {
            data[id] = res;
        }
    private:
        std::map<unsigned long, Resource*> data;
    };
}
#endif