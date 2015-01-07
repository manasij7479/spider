#ifndef SPIDER_USER_TYPE_HPP
#define SPIDER_USER_TYPE_HPP
namespace spider
{
    class UserType
    {
    public:
        enum class Type{Graph, Window, Int, NONE};
        UserType(Type t):type(t){};
        virtual void eval(std::vector<std::string> args){};
        Type type;
    };
}
#endif
