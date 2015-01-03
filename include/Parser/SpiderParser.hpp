#ifndef SPIDER_PARSER_SPIDERPARSER_HPP
#define SPIDER_PARSER_SPIDERPARSER_HPP
#include "Parser/Stream.hpp"
#include "Parser/ParseUtils.hpp"
#include "AST/AST.hpp"

namespace spider
{
    class MatchSpiderIdentifier : public Match
    {
    public:
        bool operator()(Stream& in)
        {
            Match& matcher = *Cat(Alpha(), Star(Alnum()));
            int prev = in.pos();
            bool result = matcher(in);
            if (result)
                identifier = in.range(prev, in.pos());
            return result;
        }
        std::string get()
        {
            return identifier;
        }
    private:
        std::string identifier;
    };
}
#endif