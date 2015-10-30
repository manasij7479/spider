#ifndef PARSE_UTILS_HPP
#define PARSE_UTILS_HPP
#include <functional>
#include "ParseResult.hpp"
#include "GlobalState.hpp"
#include <iostream>
namespace spc
{
    typedef std::function<ParseResult(int)> ParserFunction;
    ParserFunction LinearChoice(const std::vector<ParserFunction>& functions, std::string error = "Syntax Error")
    {
        return [=](int index) -> ParseResult
        {   
            std::vector<ParseResult> results;
            for(auto f : functions)
            {
                auto result = f(index);
                if (result)
                    return result;
                else results.push_back(result);
            }
            
            for (auto res : results)
                if (res.maybeCorrect())
                    return res;
            return ParseResult(results[0].getError() + "\n from: " + error);
        };
    }
    
    ParserFunction ZeroOrMore(const ParserFunction& f)
    {
        return [=](int index) -> ParseResult
        {
            std::vector<ASTNode*> data;
            std::string err;
            while(true)
            {
                auto result = f(index);
                if (result == false)
                {
                    if (result.maybeCorrect())
                        err = result.getError();
                    break;
                }
                else
                {
                    index = result.nextIndex();
                    data.push_back(result.get());
                }
//                 std::cerr << "STAR\n";
            }
            ParseResult result(new ASTNodeVector(data), index);
            if (err != "")
                result.setError(err);
            return result;
        };
    }
    
    ParserFunction Sequence(const std::vector<ParserFunction>& functions)
    {
        return [=](int index) -> ParseResult
        {
            bool partial = false;
            std::vector<ASTNode*> data;
            for(auto f : functions)
            {
                auto result = f(index);
                if (!result)
                {
                    if (partial)
                        result.maybeCorrect() = true;
                    return result;
                }
                else
                {
                    index = result.nextIndex();
                    data.push_back(result.get());
                    partial = true;
                }
//                 std::cerr << "SEQ\n";
            }
            return ParseResult(new ASTNodeVector(data), index);
        };
    }
    
    ParserFunction Optional(ParserFunction f)
    {
        return [=](int index) -> ParseResult
        {
            auto result = f(index);
            if (!result)
                return ParseResult(nullptr, index);
            else return result;
        };
    }
    
    template<typename ResultType>
    // ResultType must derive from ASTNode
    ParserFunction hook(ParserFunction f, ResultType*& result)
    {
        return [&](int index) -> ParseResult
        {
            auto temp = f(index);
            if(!temp)
            {
                result = nullptr;
                return temp;
            }
            result = static_cast<ResultType*>(temp.get());
//             result->dump(0, std::cerr);
            return temp;
        };
    }
    //FIXME: hook segfaults in ZeroOrMore in ParseExprList
    template<>
    ParserFunction hook<ParseResult>(ParserFunction f, ParseResult*& result)
    {
        return [&](int index) -> ParseResult
        {
            result = new ParseResult(f(index));
//             result->dump(0, std::cerr);
            return *result;
        };
    }
    
    template<typename F>
    ParserFunction hook(ParserFunction f, F callback)
    {
        return [&](int index) -> ParseResult
        {
            auto result = f(index);
            callback(result);
            return result;
        };
    }
    
    //FIXME: segfault if capture by reference :/


}
#endif