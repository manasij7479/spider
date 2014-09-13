#ifndef SPIDER_PARSER_PARSEUTILS_HPP
#define SPIDER_PARSER_PARSEUTILS_HPP
#include "Parser/Stream.hpp"
namespace spider
{
    class Match
    {
    public:
        virtual bool operator()(Stream& in)
        {
            return false;
        }
        void resetStream(Stream& stream)
        {
            stream.reset();
        }
    };
    class MatchExact : public Match
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
    template <int N>
    class MatchNOrMore : public Match
    {
    public:
        MatchNOrMore(Match* m):matcher(*m),pos(0),n(0){}
        bool operator()(Stream& in)
        {
            pos  = in.pos();
            int lastgoodpos=pos;
            while(matcher(in))
            {
                lastgoodpos = in.pos();
                n++;
            }
            in.reset(lastgoodpos);
            return (n > N);
        }
        void resetStream(Stream& stream)
        {
            stream.reset(pos);
        }
        int count(){return n;}
    private:
        Match& matcher;
        int pos;
        int n;
    };
    typedef MatchNOrMore<0> MatchZeroOrMore;
    
    
}
#endif