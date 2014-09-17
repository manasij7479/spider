#ifndef SPIDER_RESMAN_HPP
#define SPIDER_RESMAN_HPP
#include "Resource/Resource.hpp"
#include "Resource/ResourceBucket.hpp"
#include <map>
namespace spider
{
    class ResourceManager
    {
    public:
        ResourceManager():head(1){}
        unsigned long store(Resource* res)
        {
            if (res == nullptr)
                return 0;
            if (res->resTypeName() == "none")
                return 0;
            
        }
        Resource* get(unsigned long id)
        {
            auto it1 = idtype.find(id);
            if (it1 == idtype.end())
                return nullptr;//Not stored
            auto it2 = buckets.find(it1->second);
            if (it2 == buckets.end())
                return nullptr;//Something is broken
            return it2->second->get(id);
        }
    private:
        unsigned long head;
        std::map<unsigned long, std::string> idtype;
        std::map<std::string, ResourceBucket*> buckets;
    };
}
#endif