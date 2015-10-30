#ifndef CALLBACKS_HPP
#define CALLBACKS_HPP
#include "TokenTypes.hpp"
#include "GlobalState.hpp"
#include <stdexcept>
using namespace spc;
void scanInt(std::string str, int line)
{
    insertToken(new IntLiteralToken(std::stoi(str), line));
}
void scanFloat(std::string str, int line)
{
    insertToken(new FloatLiteralToken(std::stof(str), line));
}
void scanString(std::string str, int line)
{
    insertToken(new StringLiteralToken(str, line));
}
void scanSpecial(std::string str, int line)
{
    insertToken(new SpecialLiteralToken(str, line));
}
void scanIdentifier(std::string str, int line)
{
    insertToken(new IdentifierToken(str, line));
}

void scanSymbol(std::string str, int line)
{
    insertToken(new SymbolToken(str, line));
}

void reportUnexpected(std::string str, int line)
{
    throw std::runtime_error("Unexpected '"+str+"' in input.");
}

#endif