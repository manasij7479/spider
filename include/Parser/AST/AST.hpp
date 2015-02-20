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
    public:
        Identifier(std::string name_):name(name_){};
        
    private:
        std::string name;
    };
    class NumLiteral : public Expr
    {
    public:
        NumLiteral(int value_):value(value_){};
    
    private:
        int value;
    };
    
    class CallExpr : public Expr
    {
    public:
        CallExpr(Expr* expr_, std::vector<Expr*> args_):expr(expr_),args((args_)){}
    private:
        Expr* expr;
        std::vector<Expr*> args;
    };
    
    class IfExpr : public Expr
    {
    public:
        IfExpr(Expr* cond_, Expr* texpr_, Expr* fexpr_):cond(cond_),texpr(texpr_),fexpr(fexpr_){};
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
    private:
        
    };
    class AssignStmt : public Stmt
    {
    public:
        AssignStmt(Identifier* idf_, Expr* expr_):idf(idf_),expr(expr_){};
    private:
        Identifier* idf;
        Expr* expr;
    };
    class EvalStmt : public Stmt
    {
    public:
        EvalStmt(Expr* expr_):expr(expr_){};
    private:
        Expr* expr;
    };
    
}
#endif