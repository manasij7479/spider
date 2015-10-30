#ifndef PARSE_STMT_HPP
#define PARSE_STMT_HPP
#include "ParseExpr.hpp"
namespace spider
{
    ParseResult parseStmt(int index);
    /*
     * assignstmt <- identifier = Expr;
     */
    ParseResult parseAssignStmt(int index)
    {
        IdExpr* lv;
        Expr* rv;
        auto f = Sequence
        (
            {
                hook(parseIdentifierExpr,lv),
                parseEqualSymbol, 
                hook(parseExpr, rv),
                parseSemicolon
            }
        );
        
        auto result = f(index);
        if (!result)
            return result;
        
        return ParseResult(new AssignStmt(lv, rv), result.nextIndex());
    }
    /*
     * declstmt <- auto assignstmt
     */
    ParseResult parseDeclStmt(int index)
    {
        AssignStmt* as;
        auto f = Sequence({parseAuto, hook(parseAssignStmt, as)});
        auto result = f(index);
        if (!result)
            return result;
        return ParseResult(new DeclStmt(as), result.nextIndex());
    }
    
    /*
     * stmtblock <- {stmt*}
     */
    ParseResult parseStmtBlock(int index)
    {
        auto f = Sequence({parseOpenBrace, ZeroOrMore(parseStmt), parseCloseBrace});
        auto result = f(index);
        if (!result)
            return result;
        ASTNodeVector* v = static_cast<ASTNodeVector*>(result.get());
        std::vector<Stmt*> data;
        for (auto x : static_cast<ASTNodeVector*>(v->getData()[1])->getData())
            data.push_back(static_cast<Stmt*>(x));
        return ParseResult(new StmtBlock(data), result.nextIndex());
    }
    /*
     * ifstmt <- if (expression) stmtblock (else stmtblock)? 
     */
    ParseResult parseIfStmt(int index)
    {
        Expr* c = nullptr;
        Stmt* tb = nullptr;
        Stmt* fb = nullptr;
        auto f = Sequence
        (
            {
                parseIf, parseOpenParen, hook(parseExpr, c), parseCloseParen, 
                hook(parseStmtBlock, tb),
                Optional(Sequence({parseElse, hook(parseStmtBlock, fb)}))
            }
        );
        auto result = f(index);
        if (!result)
            return result;
        else return ParseResult(new IfStmt(c, tb, fb), result.nextIndex());
    }
    /*
     * whilestmt <- while (expr) stmtblock
     */
    ParseResult parseWhileStmt(int index)
    {
        Expr* c;
        Stmt* b;
        auto f = Sequence
        (
            {
                parseWhile, 
                parseOpenParen, 
                hook(parseExpr, c),
                parseCloseParen,
                hook(parseStmtBlock, b)
            }
        );
        auto result = f(index);
        if (!result)
            return result;
        else return ParseResult(new WhileStmt(c, b), result.nextIndex());
    }
    
    /*
     * typedef <- (typedef typedef*)@? / identifier
     */
    ParseResult parseTypeDefinition(int index)
    {
        std::vector<TypeDefinition*> v;
        IdExpr* id = nullptr;
        auto f = LinearChoice
            ({
                    Sequence
                    ({
                            parseOpenParen, 
                            ZeroOrMore(parseTypeDefinition), 
                            parseCloseParen, 
                            Optional(parseAlpha)
                    }),
                    hook(parseIdentifierExpr, id)
            }, "Expected Type Definition");
        auto result = f(index);
        if (!result)
            return result;
        if (id != nullptr)
            return ParseResult(new TypeDefinition({}, id, false), result.nextIndex());
        else
        {
            ASTNodeVector* seq = static_cast<ASTNodeVector*>(result.get());
            ASTNodeVector* rec = static_cast<ASTNodeVector*>(seq->getData()[1]);
            bool hasalpha = seq->getData()[3] != nullptr;
            std::vector<TypeDefinition*> data;
            for (auto node: rec->getData())
                data.push_back(static_cast<TypeDefinition*>(node));
            return ParseResult(new TypeDefinition(data, nullptr, hasalpha), result.nextIndex());
        }
        
    }
    ParseResult parseTypeDefinitionStmt(int index)
    {
        IdExpr* id;
        TypeDefinition* td;
        auto f = Sequence
        (
            {
                parseType,
                hook(parseIdentifierExpr, id),
                hook(parseTypeDefinition, td),
                parseSemicolon
            }
        );
        auto result = f(index);
        if (!result)
            return result;
        else
            return ParseResult(new TypeDefinitionStmt(id, td), result.nextIndex());
    }
    
    /*
     * functionarg <- (identifier identifier)
     * The second identifier will be converted to a TypeDefinition once we have a sophisticated typesystem
     */
    ParseResult parseFunctionArg(int index)
    {
        IdExpr *name, *type;
        auto f = Sequence({parseOpenParen, hook(parseIdentifierExpr, type), hook(parseIdentifierExpr, name), parseCloseParen});
        auto result = f(index);
        if (!result)
            return result;
        else
            return ParseResult(new FunctionArg(name, type), result.nextIndex());
    }
    /*
     *  functionproto <- function identifier functionarg* = functionarg?
     */
    ParseResult parseFunctionProtoType(int index)
    {
        IdExpr* id;
        FunctionArg* ret = nullptr;
        auto f = Sequence({parseFunction, hook(parseIdentifierExpr, id), ZeroOrMore(parseFunctionArg), Optional(Sequence({parseEqualSymbol, hook(parseFunctionArg, ret)}))});
        auto result = f(index);
        if(!result)
            return result;
        ASTNodeVector* v = static_cast<ASTNodeVector*>(result.get());
        std::vector<FunctionArg*> data;
        for (auto x : static_cast<ASTNodeVector*>(v->getData()[2])->getData())
            data.push_back(static_cast<FunctionArg*>(x));
        
        return ParseResult(new FunctionPrototype(id, ret, data), result.nextIndex());
    }
    
    /*
     * functiondecl <- functionproto ;
     */
    ParseResult parseFunctionDeclarationStmt(int index)
    {
        FunctionPrototype* p;
        auto f = Sequence({hook(parseFunctionProtoType, p), parseSemicolon});
        auto result = f(index);
        if (!result)
            return result;
        else return ParseResult(new FunctionDeclaration(p), result.nextIndex());
    }
    /*
     * functiondef <-functionproto  stmtblock
     */
    ParseResult parseFunctionDefinitionStmt(int index)
    {
        FunctionPrototype* proto;
        StmtBlock* block;
        auto f = Sequence({hook(parseFunctionProtoType, proto), hook(parseStmtBlock, block)});
        auto result = f(index);
        if (!result)
            return result;
        else return ParseResult(new FunctionDefinition(proto, block), result.nextIndex());
    }
    
    /*
     * voidcallstmt <- prefixcallexpr;
     */
    ParseResult parseVoidCallStmt(int index)
    {
        CallExpr* ce;
        auto f  = Sequence({LinearChoice({hook(parsePrefixCallExpr, ce), hook(parseInfixCallExpr, ce)}), parseSemicolon});
        auto result = f(index);
        if (!result)
            return result;
        else return ParseResult(new VoidCallStmt(ce), result.nextIndex());
    }
    
    /*
     * importstmt <- import stringliteral;
     */
    ParseResult parseImportStmt(int index)
    {
        StringLiteralExpr* s;
        auto f = Sequence({parseImport, hook(parseStringLiteralExpr, s), parseSemicolon});
        auto result = f(index);
        if (!result)
            return result;
        else return ParseResult(new ImportStmt(s), result.nextIndex());
        
    }
    ParseResult parseStmt(int index)
    {
        return LinearChoice
        (
            {
                parseAssignStmt,
                parseDeclStmt,
                parseIfStmt,
                parseWhileStmt,
                parseStmtBlock,
                parseImportStmt,
                parseVoidCallStmt,
                parseFunctionDeclarationStmt,
                parseFunctionDefinitionStmt
            },
            "Expected Statement"
        )
        (index);
    }
}
#endif