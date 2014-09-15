#ifndef SPIDER_PARSE_UTILS_HPP
#define SPIDER_PARSE_UTILS_HPP
#include "Parser/Matchers.hpp"
namespace spider
{
    Match* Direct(std::string str)
    {
        return new MatchExact(str);
    }
    
    Match* Star(Match* m)
    {
        return new MatchZeroOrMore(m);
    }
    Match* Plus(Match* m)
    {
        return new MatchOneOrMore(m);
    }
    
    Match* Cat(std::vector<Match*> m)
    {
        return new MatchAll(m);
    }
    Match* Cat(Match* a, Match* b)
    {
        return new MatchAll({a,b});
    }
    
    Match* Any(std::vector<Match*> m)
    {
        return new MatchAny(m);
    }
    Match* Any(Match* a, Match* b)
    {
        return new MatchAny({a,b});
    }
    
    
    Match* CharClass(char first, char last)
    {
        return new MatchCharClass(first,last);
    }
    
    Match* Alpha()
    {
        return Any(CharClass('a','b'),CharClass('A','B'));
    }
    Match* Digit()
    {
        return new MatchCharClass('0','9');
    }
    Match* Alnum()
    {
        return Any(Alpha(),Digit());
    }
}
#endif