#ifndef AST_HPP
#define AST_HPP
#include "TokenTypes.hpp"
#include <iostream>
#include <vector>
namespace spider
{
    class Sema;
    void tabs(int t, std::ostream& out = std::cout);
    
    class ASTNode
    {
    public:
        ASTNode();
        virtual void dump(int tab=0, std::ostream& out = std::cout);
    };
    class ASTNodeVector : public ASTNode
    {
    public:
        ASTNodeVector(std::vector<ASTNode*> d):data(d){}
    private:
        std::vector<ASTNode*> data;
    public:
        auto getData(){return data;}
        virtual void dump(int tab=0, std::ostream& out = std::cout);
    };
    class Expr : public ASTNode
    {
    public:
        enum class Type
        {
            Id,
            Int,
            Float,
            String,
            Bool,
            List,
            Call,
            Special
        };
        Expr(Type t):type(t){}
        Type type;
    };
    typedef Expr::Type EType;

    class IdExpr : public Expr
    {
    public:
        IdExpr(IdentifierToken* id_):Expr(EType::Id),id(id_){}
    private:
        IdentifierToken* id;
    public:
        auto getToken(){return id;}
        virtual void dump(int tab=0, std::ostream& out = std::cout);
    };
    class IntLiteralExpr: public Expr
    {
    public:
        IntLiteralExpr(IntLiteralToken* it):Expr(EType::Int),i(it){}
    private:
        IntLiteralToken* i;
    public:
        auto getToken(){return i;}
        virtual void dump(int tab=0, std::ostream& out = std::cout);
    };
    class FloatLiteralExpr: public Expr
    {
    public:
        FloatLiteralExpr(FloatLiteralToken* ft):Expr(EType::Float),f(ft){}
    private:
        FloatLiteralToken* f;
    public:
        auto getToken(){return f;}
        virtual void dump(int tab=0, std::ostream& out = std::cout);
    };
    class StringLiteralExpr: public Expr
    {
    public:
        StringLiteralExpr(StringLiteralToken* st):Expr(EType::String),s(st){}
    private:
        StringLiteralToken* s;
    public:
        auto getToken(){return s;}
        virtual void dump(int tab=0, std::ostream& out = std::cout);
    };
    
    class BoolLiteralExpr: public Expr
    {
    public:
        BoolLiteralExpr(SymbolToken* st):Expr(EType::Bool),sym(st){}
    private:
        SymbolToken* sym;
    public:
        auto getToken(){return sym;}
        virtual void dump(int tab=0, std::ostream& out = std::cout);
    };
    
    class ExprList : public Expr
    {
    public:
        ExprList(std::vector<Expr*> el):Expr(EType::List), data(el){}
    private:
        std::vector<Expr*> data;
    public:
        auto getData(){return data;}
        virtual void dump(int tab=0, std::ostream& out = std::cout);
    };
    
    class CallExpr : public Expr
    {
    public:
        CallExpr(IdExpr* id, ExprList* el):Expr(EType::Call), fname(id), args(el){}
    private:
        IdExpr* fname;
        ExprList* args;
    public:
        auto getCallee(){return fname;}
        auto getArgs(){return args;}
        virtual void dump(int tab=0, std::ostream& out = std::cout);
    };

    class SpecialTokenNode : public ASTNode
    {
    public:
    SpecialTokenNode(SpecialLiteralToken* sp_):sp(sp_){}
    private:
        SpecialLiteralToken* sp;
    public:
        auto getData(){return sp->data;}
        virtual void dump(int tab=0, std::ostream& out = std::cout);
    };
    class SpecialExpr : public Expr
    {
    public:
        SpecialExpr(SpecialTokenNode* sp_, ExprList* el):Expr(EType::Special), sp(sp_), args(el){}
    private:
        SpecialTokenNode* sp;
        ExprList* args;
    public:
        auto getSpecialToken(){return sp;}
        auto getArgs(){return args;}
        virtual void dump(int tab=0, std::ostream& out = std::cout);
    };
      
    class Stmt : public ASTNode
    {
    public:
        enum class Type
        {
            Assign,
            Decl,
            While,
            If,
            Block,
            Type,
            FDef,
            FDecl,
            VCall,
            Import
        };
        Stmt(Type t):type(t){}
        Type type;
    };
    typedef Stmt::Type SType;
    
    class AssignStmt : public Stmt
    {
    public:
        AssignStmt(IdExpr* lv, Expr* rv);
    private:
        IdExpr* lvalue;
        Expr* rvalue;
    public:
        auto getLvalue(){return lvalue;}
        auto getRvalue(){return rvalue;}
        virtual void dump(int tab=0, std::ostream& out = std::cout);
    };
    
    class DeclStmt : public Stmt
    {
        //there will be semantic difference
    public:
        DeclStmt(AssignStmt* as);
    private:
        AssignStmt* stmt;
    public:
        auto getAssignStmt(){return stmt;}
        virtual void dump(int tab=0, std::ostream& out = std::cout);
    };
    
    class IfStmt : public Stmt
    {
    public:
        IfStmt(Expr* c, Stmt* t, Stmt* f);
    private:
        Expr* condition;
        Stmt* trueblock;
        Stmt* falseblock;
    public:
        auto getCondition(){return condition;}
        auto getTrueBlock(){return trueblock;}
        auto getFalseBlock(){return falseblock;}
        virtual void dump(int tab=0, std::ostream& out = std::cout);
    };
    
    class WhileStmt : public Stmt
    {
    public:
        WhileStmt(Expr* c, Stmt* b);
    private:
        Expr* condition;
        Stmt* block;
    public:
        auto getCondition(){return condition;}
        auto getBlock(){return block;}
        virtual void dump(int tab=0, std::ostream& out = std::cout);
    };
    
    class VoidCallStmt : public Stmt
    {
    public:
        VoidCallStmt(CallExpr* c);
    private:
        CallExpr* expr;
    public:
        auto getCallExpr(){return expr;}
        virtual void dump(int tab=0, std::ostream& out = std::cout);
    };
    
    class StmtBlock : public Stmt
    {
    public:
        StmtBlock(std::vector<Stmt*> d):Stmt(SType::Block), data(d){}
    private:
        std::vector<Stmt*> data;
    public:
        auto getData(){return data;}
        virtual void dump(int tab=0, std::ostream& out = std::cout);
    };
    
    class TypeDefinition : public ASTNode
    {
    public:
        TypeDefinition(std::vector<TypeDefinition*> d, IdExpr* i, bool alpha): data(d), id(i), is_array(alpha){}
    private:
        IdExpr* id; // exists if builtin or named
        std::vector<TypeDefinition*> data;
        bool is_array;
    public:
        virtual void dump(int tab=0, std::ostream& out = std::cout);
    };
    
    class TypeDefinitionStmt: public Stmt
    {
    public:
        TypeDefinitionStmt(IdExpr* i, TypeDefinition* td);
    private:
        IdExpr* id;
        TypeDefinition* def;
    public:
        virtual void dump(int tab=0, std::ostream& out = std::cout);
    };
    
//     class ReturnStmt : public Stmt
//     {
//     public:
//         ReturnStmt(Expr* e):Stmt(SType::Ret), expr(e){}
//     private:
//         Expr* expr;
//     public:
//         virtual void dump(int tab=0, std::ostream& out = std::cout);
//     };
    
//     template <typename T>
//     T* getAs(ASTNode* node ,std::vector<int> loc={})
//     {
//         if (loc.empty())
//             return static_cast<T*>(node);
//         ASTNodeVector* v = getAs<ASTNodeVector>(node);
//         if (loc.size() == 1)
//             return static_cast<T*>(v->getData()[loc[0]]);
//         
//         int x = loc[0];
//         loc.erase(loc.begin());
//         return getAs<T>(getAs<ASTNode>(v, {x}) ,loc);
//     }
    class FunctionArg: public ASTNode
    {
    public:
        FunctionArg(IdExpr* name_, IdExpr* type_);
        auto getName(){return name;}
        auto getTypeName(){return type;}
    private:
        IdExpr* name;
        IdExpr* type;
    public:
        virtual void dump(int tab=0, std::ostream& out = std::cout);
    };
    class FunctionPrototype: public ASTNode
    {
    public:
        FunctionPrototype(IdExpr* id_, FunctionArg* ret_, std::vector<FunctionArg*> args_);
        auto getName(){return id;}
        auto getReturnArg(){return ret;}
        auto getArgs(){return args;}
    private:
        IdExpr* id;
        FunctionArg* ret;
        std::vector<FunctionArg*> args;
    public:
        virtual void dump(int tab=0, std::ostream& out = std::cout);
    };
    class FunctionDefinition: public Stmt
    {
    public:
        FunctionDefinition(FunctionPrototype* proto_, StmtBlock* block_);
        auto getPrototype(){return proto;}
        auto getBlock(){return block;}
    private:
        FunctionPrototype* proto;
        StmtBlock* block;
    public:
        virtual void dump(int tab=0, std::ostream& out = std::cout);
    };
    
    class FunctionDeclaration: public Stmt
    {
    public:
        FunctionDeclaration(FunctionPrototype* proto_);
        auto getPrototype(){return proto;}
    private:
        FunctionPrototype* proto;
    public:
        virtual void dump(int tab=0, std::ostream& out = std::cout);
    };
    
    class ImportStmt : public Stmt
    {
    public:
        ImportStmt(StringLiteralExpr* s):Stmt(SType::Import),str(s){}
        auto getStr(){return str;}
    private:
        StringLiteralExpr* str;
    public:
        virtual void dump(int tab=0, std::ostream& out = std::cout);
    };
}
#endif