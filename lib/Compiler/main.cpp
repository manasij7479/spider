#include <iostream>
#include <fstream>
#include "GlobalState.hpp"
#include "ParseStmt.hpp"
#include "Sema.hpp"
#include <cstdio>
int main(int argc, char** argv)
{
    spc::exepath = argv[0];
    if (argc < 2)
    {
        std::cerr << "Expected Filename or - (for stdin).";
        return 1;
    }
    if (std::string(argv[1]) != "-")
    {
        yyin = std::fopen(argv[1], "r");
        if (!yyin)
        {
            std::cerr << "Can not open file: " << argv[1];
            return 1;
        }
    }
    spc::pushState();
    yylex();
    
    std::ostream* out = &std::cout;
    if (argc == 3 && std::string(argv[2]) != "-" )
    {
        out = new std::ofstream(argv[2]);
        if (!out)
            std::cerr << "Can not open file: " << argv[2];
    }
    
    spc::insertToken(new spc::EOFToken);
    auto p = spc::ZeroOrMore(spc::parseStmt)(0);
    
    if (!p)
        std::cerr << "ERROR: " << p.getError() << std::endl;
    else
    {
        if (p.getError() != "")
            std::cerr << "HEURISTICS: " << p.getError() << std::endl;
//         std::cout << "Parsed" << std::endl;
//         if (p.get() != nullptr)
//             p.get()->dump();
        spc::ASTNodeVector* v = static_cast<spc::ASTNodeVector*>(p.get());
        std::vector<spc::ASTNode*> data = v->getData();
        spc::Sema s(out);
        for (auto node : data)
        {
//             static_cast<spc::Stmt*>(node)->dump();
            s.process(static_cast<spc::Stmt*>(node));
        }
    }
    spc::popState();
    return 0;
}
