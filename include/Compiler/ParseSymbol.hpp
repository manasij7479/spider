#ifndef PARSE_SYMBOL_HPP
#define PARSE_SYMBOL_HPP
#include "GlobalState.hpp"
#include "AST.hpp"
#include "ParseResult.hpp"
#include "ParseUtils.hpp"
namespace spc
{
    bool isCorrectSymbol(int index, std::string s)
    {
        return getToken(index)->type == TType::Symbol
            && getsy(getToken(index))->data == s;
    }
    
    ParseResult parsePrefixSymbol(int index)
    {
        if (!isCorrectSymbol(index, "'"))
            return ParseResult("Line: '" 
                + std::to_string(getToken(index)->line)
                + "' ::Expected " + "'" +" symbol.");
        else return ParseResult(new ASTNode(), index + 1);
    }
    ParseResult parseEqualSymbol(int index)
    {
        if (!isCorrectSymbol(index, "="))
            return ParseResult("Line: '" 
                + std::to_string(getToken(index)->line)
                + "' ::Expected " + "=" +" symbol.");
        else return ParseResult(new ASTNode(), index + 1);
    }
    ParseResult parseOpenParen(int index)
    {
        if (!isCorrectSymbol(index, "("))
            return ParseResult("Line: '" 
                + std::to_string(getToken(index)->line)
                + "' ::Expected " + "(" +" symbol.");
        else return ParseResult(new ASTNode(), index + 1);
    }
    ParseResult parseCloseParen(int index)
    {
        if (!isCorrectSymbol(index, ")"))
                return ParseResult("Line: '" 
                    + std::to_string(getToken(index)->line)
                    + "' ::Expected " + ")" +" symbol.");
        else return ParseResult(new ASTNode(), index + 1);
    }
    
    ParseResult parseOpenBrace(int index)
    {
        if (!isCorrectSymbol(index, "{"))
            return ParseResult("Line: '" 
                + std::to_string(getToken(index)->line)
                + "' ::Expected " + "{" +" symbol.");
        else return ParseResult(new ASTNode(), index + 1);
    }
    ParseResult parseCloseBrace(int index)
    {
        if (!isCorrectSymbol(index, "}"))
                return ParseResult("Line: '" 
                    + std::to_string(getToken(index)->line)
                    + "' ::Expected " + "}" +" symbol.");
        else return ParseResult(new ASTNode(), index + 1);
    }
    
    ParseResult parseSemicolon(int index)
    {
        if (!isCorrectSymbol(index, ";"))
                return ParseResult("Line: '" 
                    + std::to_string(getToken(index)->line)
                    + "' ::Expected " + ";" +" symbol.");
        else return ParseResult(new ASTNode(), index + 1);
    }
    
    ParseResult parseAlpha(int index)
    {
        if (!isCorrectSymbol(index, "@"))
            return ParseResult("Line: '" 
                + std::to_string(getToken(index)->line)
                + "' ::Expected " + "@" +" symbol.");
        else return ParseResult(new ASTNode(), index + 1);
    }
    
    ParseResult parseAuto(int index)
    {
        if (!isCorrectSymbol(index, "auto"))
            return ParseResult("Line: '" 
                + std::to_string(getToken(index)->line)
                + "' ::Expected " + "auto" +" symbol.");
        else return ParseResult(new ASTNode(), index + 1);
    }
    ParseResult parseIf(int index)
    {
        if (!isCorrectSymbol(index, "if"))
            return ParseResult("Line: '" 
                + std::to_string(getToken(index)->line)
                + "' ::Expected " + "if" +" symbol.");
        else return ParseResult(new ASTNode(), index + 1);
    }
    ParseResult parseElse(int index)
    {
        if (!isCorrectSymbol(index, "else"))
            return ParseResult("Line: '" 
                + std::to_string(getToken(index)->line)
                + "' ::Expected " + "else" +" symbol.");
        else return ParseResult(new ASTNode(), index + 1);
    }
    ParseResult parseWhile(int index)
    {
        if (!isCorrectSymbol(index, "while"))
            return ParseResult("Line: '" 
                + std::to_string(getToken(index)->line)
                + "' ::Expected " + "while" +" symbol.");
        else return ParseResult(new ASTNode(), index + 1);
    }

    ParseResult parseReturn(int index)
    {
        if (!isCorrectSymbol(index, "return"))
            return ParseResult("Line: '" 
                + std::to_string(getToken(index)->line)
                + "' ::Expected " + "return" +" symbol.");
        else return ParseResult(new ASTNode(), index + 1);
    }

    ParseResult parseType(int index)
    {
        if (!isCorrectSymbol(index, "type"))
            return ParseResult("Line: '" 
                + std::to_string(getToken(index)->line)
                + "' ::Expected " + "type" +" symbol.");
        else return ParseResult(new ASTNode(), index + 1);
    }

    ParseResult parseFunction(int index)
    {
        if (!isCorrectSymbol(index, "function"))
            return ParseResult("Line: '" 
                + std::to_string(getToken(index)->line)
                + "' ::Expected " + "function" +" symbol.");
        else return ParseResult(new ASTNode(), index + 1);
    }
    
    ParseResult parseImport(int index)
    {
        if (!isCorrectSymbol(index, "import"))
            return ParseResult("Line: '" 
                + std::to_string(getToken(index)->line)
                + "' ::Expected " + "import" +" symbol.");
        else return ParseResult(new ASTNode(), index + 1);
    }
    

    
}
#endif