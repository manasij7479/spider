#ifndef GLOBAL_STATE_HPP
#define GLOBAL_STATE_HPP
#include <vector>
#include "TokenTypes.hpp"
extern "C" int yylex();
extern FILE* yyout;
extern FILE* yyin;
typedef struct yy_buffer_state * YY_BUFFER_STATE;
extern YY_BUFFER_STATE yy_scan_string(const char * str);
extern void yy_delete_buffer(YY_BUFFER_STATE buffer);

namespace spider
{
    extern std::vector<std::vector<Token*>> Tokens;
    extern std::string exepath;
    inline void insertToken(Token* t)
    {
        Tokens.back().push_back(t);
    }
    inline Token* getToken(int index)
    {
        return Tokens.back()[index];
    }
    inline void pushState()
    {
        Tokens.push_back(std::vector<Token*>());
    }
    inline void popState()
    {
        Tokens.pop_back();
    }
//When possible, make flex generate C++ code, making this unnecessary
//That feature is still experimental and does not properly support multiple scanners yet.
}
#endif
