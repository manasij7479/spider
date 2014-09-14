#ifndef SPIDER_PARSER_PARSEUTILS_HPP
#define SPIDER_PARSER_PARSEUTILS_HPP
#include "Parser/Stream.hpp"
// #include <iostream>
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
            {
//                 std::cout << in.peek() <<'\t' << c<<'\n';
                if(in.peek()!=c)
                    return false;
                in.get();
            }
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
            return (n >= N);
        }
        void resetStream(Stream& stream)
        {
            stream.reset(pos);
        }
        int count()
        {
            return n;
        }
        void reset()
        {
            pos=0;
            n=0;
        }
    private:
        Match& matcher;
        int pos;
        int n;
    };
    typedef MatchNOrMore<0> MatchZeroOrMore;
    typedef MatchNOrMore<1> MatchOneOrMore;
    
    class MatchAny : public Match
    {
    public:
        MatchAny(std::vector<Match*> matchers_):matchers(matchers_),correct(-1),pos(0){};
        int which()
        {
            int i = correct;
            correct = -1;
            return i;
        }
        bool operator()(Stream& in)
        {
            pos = in.pos();
            for (int i = 0; i < matchers.size(); ++i)
            {
                int lastgoodpos = in.pos();
                Match& matcher = * matchers[i];
                if (matcher(in))
                {
                    correct = i;
                    return true;
                }
                else in.reset(lastgoodpos);
            }
            
            return false;
        }
        void reset()
        {
            pos = 0;
            correct = -1;
        }
        void resetStream(Stream& stream)
        {
            stream.reset(pos);
        }
    private:
        std::vector<Match*> matchers;
        int correct;
        int pos;
    };
    
    //Have to memoize partial matches somehow
    class MatchAll : public Match
    {
    public:
        MatchAll(std::vector<Match*> matchers_):matchers(matchers_),pos(0),n(0){};
        bool operator()(Stream& in)
        {
            pos = in.pos();
            for (auto m : matchers)
            {
                Match& matcher = *m;
                if (! matcher(in))
                    return false;
                n++;
            }
            return true;
        }
        void resetStream(Stream& stream)
        {
            stream.reset(pos);
        }
        int count()
        {
            return n;
        }
        void reset()
        {
            pos=0;
            n=0;
        }
    private:
        std::vector<Match*> matchers;
        int pos;
        int n;
    };
    
    class MatchCharClass : public Match
    {
    public:
        MatchCharClass(char first_, char last_, int step_ = 1):first(first_),last(last_),step(step_), pos(0),correct(0){}
        bool operator()(Stream& in)
        {
            pos=in.pos();
            //Binary Search here
            for(char c = first; c <= last; c+=step)
            {
                
                if(in.peek() == c)
                {
                    correct = in.get();
                    return true;
                }
            }
            return false;
        }
        char which()
        {
            return correct;
        }
        void reset()
        {
            pos=0;
            correct=0;
        }
        void resetStream(Stream& stream)
        {
            stream.reset(pos);
        }
    private:
        char first;
        char last;
        int step;
        int pos;
        char correct;
    };
    
    
}
#endif