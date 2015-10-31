#ifndef SPIDER_COMPILER_FRONTEND
#define SPIDER_COMPILER_FRONTEND
#include "Compiler/AST.hpp"
#include "Compiler/ParseUtils.hpp"
#include "Compiler/ParseStmt.hpp"
#include "Compiler/GlobalState.hpp"
#include "Compiler/ParseStmt.hpp"
#include "Compiler/Sema.hpp"
#include <cstdio>

#include <memory>
#include <sstream>
namespace spider
{
    //Low level API
    //TODO: Make better abstractions
    //TODO: Use smart pointer
    std::pair<ASTNode*, std::string> compile_string_to_ast(const std::string& in)
    {
        spider::pushState();
        auto bufstate = yy_scan_string(in.c_str());
        yylex();

        std::ostringstream error;
        insertToken(new EOFToken);
        auto p = ZeroOrMore(parseStmt)(0);

        if (!p)
            error << "ERROR: " << p.getError() << std::endl;
        else if (p.getError() != "")
                error << "HEURISTICS: " << p.getError() << std::endl;

        yy_delete_buffer(bufstate);
        spider::popState();
        return {p.get(), error.str()};
    }
}
#endif
