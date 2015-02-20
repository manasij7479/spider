#ifndef SPIDER_LEXER_HPP
#define SPIDER_LEXER_HPP
#include "Parser/Stream.hpp"
#include <vector>
#include <string>
#include <regex>
#include <functional>

namespace spider
{
    class Lexer
    {
    public:
        typedef std::function<void(std::string)> Callback;
        typedef std::vector<std::pair<std::string, Callback>> List;
        Lexer(const List& m,Stream& in):
            matchers(m), stream(in) {}
        void processNext()
        {
            
        }
    private:
        List matchers;
        Stream& stream;
    };
}
#endif