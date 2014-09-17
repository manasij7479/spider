#ifndef SPIDER_RESOURCE_HPP
#define SPIDER_RESOURCE_HPP
namespace spider
{
    class Resource
    {
    public:
        virtual bool isSame(Resource* res){return false;}
        virtual std::string resTypeName(){return "none";}
    };
}
#endif