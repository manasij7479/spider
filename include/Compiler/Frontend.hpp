#ifndef SPIDER_COMPILER_FRONTEND
#define SPIDER_COMPILER_FRONTEND
#include "Compiler/AST.hpp"
#include "Compiler/ParseUtils.hpp"
#include "Compiler/ParseStmt.hpp"
#include <memory>
namespace spider
{
    //Low level API
    //TODO: Make better abstractions
    //TODO: Use smart pointer
    std::pair<ASTNode*, std::string> compile_string_to_ast(const std::string& in)
    {
        //TODO : copy stuff from main in spider-compiler
        return {nullptr,"This is a placeholder."};
    }
}
#endif