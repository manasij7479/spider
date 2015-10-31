#ifndef SEMA_HPP
#define SEMA_HPP
#include "AST.hpp"
#include "SymbolTable.hpp"
#include "GlobalState.hpp"
#include <map>
#include <sstream>
#include <stdio.h>
#include <functional>
#include "ParseResult.hpp"
#include <cctype>
namespace spider
{
    std::function<ParseResult(int)> ZeroOrMore(const std::function<ParseResult(int)>& f);
    ParseResult parseStmt(int index);
    class Sema
    {
    public:
        Sema(std::ostream* out)
        {
            output_stack.push_back(out);
        }
        
        void process(Stmt* s);
        void process(DeclStmt* ds);
        void process(AssignStmt* as);
        void process(StmtBlock* b);
        void process(IfStmt* ifs);
        
        void process(WhileStmt* ws);
        
        void process(FunctionPrototype* fp, bool codegen = false);
        void process(VoidCallStmt* vstmt)
        {
            auto p = process(vstmt->getCallExpr(),/*assign=*/ false);
            //ignore the result for now
            //needs checking, maybe warnings too if type is not void
        }
        void process(FunctionDeclaration* fd)
        {
            process(fd->getPrototype());
        }
        void process(FunctionDefinition* fd)
        {
            process(fd->getPrototype(), true /*codegen*/);
            
            process(fd->getBlock());
        }
        void process(ImportStmt* imp);
        std::string convert_into_function(Expr* e); // returns function name
        std::pair<std::string, Type> process(Expr* e);
        std::pair<std::string, Type> process(CallExpr* ce, bool assign = true);

        std::pair<std::string, Type> process(SpecialExpr* ce);
        void output(std::string s, bool endl = true);
    private:
        //bool type_check(); //decide on the interface!
        //TODO: Symbol Table, Function Sigs, etc.
        
        std::vector<std::ostream*> output_stack;
        SymbolTable table;
        std::string getReturnType(std::string f);
        std::vector<std::pair<std::string, std::string>> getArgTypeList(std::string f);
    };
}
#endif
