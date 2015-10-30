#ifndef PARSE_EXPR_HPP
#define PARSE_EXPR_HPP
#include "ParseSymbol.hpp"
#include <iostream>
namespace spider
{
    ParseResult parseExpr(int index);
    ParseResult parseIntLiteralExpr(int index)
    {
        if (getToken(index)->type == TType::IntLiteral)
        {
            return ParseResult(new IntLiteralExpr(getil(getToken(index))), index+1);
        }
        else return ParseResult("Line: '" + std::to_string(getToken(index)->line)+"' ::Expected Int Literal");
    }
    ParseResult parseFloatLiteralExpr(int index)
    {
        if (getToken(index)->type == TType::FloatLiteral)
        {
            return ParseResult(new FloatLiteralExpr(getfl(getToken(index))), index+1);
        }
        else return ParseResult("Line: '" + std::to_string(getToken(index)->line)+"' ::Expected Float Literal");
    }
    ParseResult parseStringLiteralExpr(int index)
    {
        if (getToken(index)->type == TType::StringLiteral)
        {
            return ParseResult(new StringLiteralExpr(getsl(getToken(index))), index+1);
        }
        else return ParseResult("Line: '" 
            + std::to_string(getToken(index)->line)
            + "' ::Expected String Literal");
    }
    
    ParseResult parseBoolLiteralExpr(int index)
    {
        auto tok = getToken(index);
        if (tok->type == TType::Symbol && (getsy(tok)->data == "true" || getsy(tok)->data == "false"))
        {
            return ParseResult(new BoolLiteralExpr(getsy(getToken(index))), index+1);
        }
        else return ParseResult("Line: '" 
            + std::to_string(getToken(index)->line)
            + "' ::Expected Bool Literal (true/false)");
    }
    
    ParseResult parseIdentifierExpr(int index)
    {
        if (getToken(index)->type == TType::Identifier)
        {
            return ParseResult(new IdExpr(getifr(getToken(index))), index+1);
        }
        else return ParseResult("Line: '" 
                + std::to_string(getToken(index)->line)
                + "' ::Expected Identifier");
    }
    ParseResult parseSpecialTokenNode(int index)
    {
        if (getToken(index)->type == TType::SpecialLiteral)
        {
            return ParseResult(new SpecialTokenNode(getspc(getToken(index))), index+1);
        }
        else return ParseResult("Line: '" 
                + std::to_string(getToken(index)->line)
                + "' ::Expected Special Token");
    }
    
    /*
     * exprlist <- expr*
     */
    ParseResult parseExprList(int index)
    {
        auto f = ZeroOrMore(parseExpr);
        auto result = f(index);
        if (!result)
            return result;
        std::vector<Expr*> data;
        for (auto x : static_cast<ASTNodeVector*>(result.get())->getData())
            data.push_back(static_cast<Expr*>(x));
        return ParseResult(new ExprList(data), result.nextIndex());
    }
    
//     /*
//      *  prefixcallexpr <- ' identifier expr* 
//      */
//     ParseResult parsePrefixCallExpr(int index)
//     {
//         auto f = Sequence({parsePrefixKeyword, parseIdentifierExpr, ZeroOrMore(parseExpr)});
//         auto result = f(index);
//         if (!result)
//             return result;
//         auto node = new CallExpr;
//         ASTNodeVector* v = static_cast<ASTNodeVector*>(result.get());
//         node->fname = static_cast<IdExpr*>(v->data[1]);
//         for (auto x : static_cast<ASTNodeVector*>(v->data[2])->data)
//             node->args.push_back(static_cast<Expr*>(x));
//         return ParseResult(node, result.nextIndex());
//     }
    
    
    /*
     * specialexpr <- special (exprlist)
     */
    ParseResult parseSpecialExpr(int index)
    {
        SpecialTokenNode* sp;
        ExprList* list;
        auto f = Sequence
        (
            {
                hook(parseSpecialTokenNode, sp),
                Sequence({parseOpenParen, hook(parseExprList, list), parseCloseParen})
            }
        );
        auto result = f(index);
        if(!result)
            return result;

        return ParseResult(new SpecialExpr(sp, list), result.nextIndex());
    }
    
    /*
     *  prefixcallexpr <- identifier (exprlist)
     */
    ParseResult parsePrefixCallExpr(int index)
    {
        IdExpr* id;
        ExprList* list;
        auto f = Sequence
        (
            {
//                 parsePrefixSymbol, 
                hook(parseIdentifierExpr, id),
                Sequence({parseOpenParen, hook(parseExprList, list), parseCloseParen})
            }
        );
        auto result = f(index);
        if(!result)
            return result;

        return ParseResult(new CallExpr(id, list), result.nextIndex());
    }
    
    /*
     * infixcallexpr <- ' expr identifier exprlist '?
     */
    ParseResult parseInfixCallExpr(int index)
    {
        Expr* obj;
        IdExpr* id;
        ExprList* list;
        auto f = Sequence
        (
            {
                parsePrefixSymbol,
                hook(parseExpr, obj),
                hook(parseIdentifierExpr, id),
                hook(parseExprList, list),
                Optional(parsePrefixSymbol)
            }
        );
        auto result = f(index);
        if(!result)
            return result;
        auto data = list->getData();
        data.insert(data.begin(), obj);
        return ParseResult(new CallExpr(id, new ExprList(data)), result.nextIndex());
    }
    
    /*
     * expr <- intliteral / stringliteral / identifier / prefixcallexpr
     */
    ParseResult parseExpr(int index)
    {
        return LinearChoice
        (
            {
                parseIntLiteralExpr,
                parseFloatLiteralExpr,
                parseStringLiteralExpr,
                parseBoolLiteralExpr,
                parseSpecialExpr,
                parseInfixCallExpr,
                parsePrefixCallExpr, // Would benefit from memoization
                parseIdentifierExpr,
                
            },
            "Expected Expression."
        )
        (index);
    }
    ParseResult ParseEof(int index)
    {
        if (getToken(index)->type == TType::Eof)
        {
            return ParseResult(nullptr, index); // Special case for EOF, index does not increase.
        }
        else return ParseResult("Line: '" + std::to_string(getToken(index)->line)+"' ::Expected EOF");
    }
}
#endif