#ifndef PARSE_RESULT_HPP
#define PARSE_RESULT_HPP
#include "AST.hpp"
#include <vector>
#include <sstream>
namespace spider
{
    class ParseResult
    {
    public:
        ParseResult(std::string s)
            :success(false),
             result(nullptr),
             error(s),index(-1), partial(false){}
        ParseResult(ASTNode* node, int i)
        {
            success = true;
            result = node;
            index = i;
            partial = true;
        }
        operator bool()
        {
            return success;
        }
        ASTNode* get()
        {
            return result;
        }
        std::string getError()
        {
            return error;
        }
        void setError(std::string e)
        {
            error = e;
        }
        int nextIndex()
        {
            return index;
        }
        bool& maybeCorrect()
        {
            return partial;
        }
    private:
        bool success;
        bool partial;
        ASTNode* result;
        std::string error;
        int index;
    };
}
#endif