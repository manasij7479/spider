#ifndef SPIDER_PARSER_PARSEUTILS_HPP
#define SPIDER_PARSER_PARSEUTILS_HPP
#include "Parser/Stream.hpp"
namespace spider
{
    class MatchExact
    {
    public:
        MatchExact(std::string str_):str(str_),pos(0){};
        bool operator()(Stream& in)
        {
            in.skipSpace();
            pos = in.pos();
            for(auto c:str)
                if(in.get()!=c)
                    return false;
            return true;
        }
        void resetStream(Stream& stream)
        {
            stream.reset(pos);
        }
    private:
        std::string str;
        int pos;
    };
    
    
    
}
#endif