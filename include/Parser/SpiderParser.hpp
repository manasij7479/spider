#ifndef SPIDER_PARSER_SPIDERPARSER_HPP
#define SPIDER_PARSER_SPIDERPARSER_HPP
#include "Parser/Stream.hpp"
#include "AST/AST.hpp"
namespace spider
{
    Stmt* ParseSpiderStmt(Stream& in);
}
#endif