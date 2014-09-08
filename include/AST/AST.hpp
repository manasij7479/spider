#ifndef SPIDER_AST_HPP
#define SPIDER_AST_HPP
#include <vector>
namespace spider
{
    class Expr
    {
        
    };
    class Identifier : public Expr
    {
    private:
        std::string name;
    };
    class NumLiteral : public Expr
    {
    private:
        int value;
    };
    
    class CallExpr : public Expr
    {
    private:
        Expr* function;
        std::vector<Expr*> args;
    };
    
    class IfExpr : public Expr
    {
    private:
        Expr* cond;
        Expr* texpr;
        Expr* fexpr;
    };
    
//     class SpecialExpr : public Expr
//     {
//         
//     }; 
//     //Implement later
    
    class Stmt
    {
        
    };
    class AssignStmt : public Stmt
    {
    private:
        Identifier* idf;
        Expr* expr;
    };
    class EvalStmt : public Stmt
    {
    private:
        Expr* expr;
    };
    
}
#endif