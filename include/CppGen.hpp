#ifndef SPIDER_CPPGEN_HPP
#define SPIDER_CPPGEN_HPP
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
//Only generate things we actually need
//No need to go overboard
//We do not need a whole/(or technically correct) C++ AST.
namespace spider
{
    namespace cpp
    {
        class Printable
        {
        public:
            virtual std::string str() const
            {}
        };
        std::ostream& operator<<(std::ostream& out, Printable* p)
        {
            out<<p->str();
            return out;
        }
        class Expr : public Printable
        {
        public:
            virtual std::string str() const
            {
                return "";
            }
        };
        
        class Identifier : public Expr
        {
        public:
            Identifier(std::string s):name(s){};
            std::string str() const
            {
                return name;
            }
        private:
            std::string name;
        };
        
        class Literal : public Expr
        {
        public:
            Literal(std::string s):data(s){};
            std::string str() const
            {
                return data;
            }
        private:
            std::string data;
        };
        
        class BinOp : public Printable // An operator is not an expression
        {
        public:
            BinOp(std::string s):op(s){};
            std::string str() const
            {
                return op;
            }
        private:
            std::string op;
        };
        
        class BinExpr : public Expr
        {
        public:
            BinExpr(Expr* lhs_,Expr* rhs_,BinOp* op_):
                lhs(lhs_),rhs(rhs_),op(op_){};
                
            std::string str() const
            {
                std::ostringstream out;
                out<<"("<<lhs<<op<<rhs<<")";
                return out.str();
            }
        private:
            Expr* lhs;
            Expr* rhs;
            BinOp* op;
        };
        
        class FunctionCallExpr : public Expr
        {
        public:
            FunctionCallExpr(std::string name_, std::vector<Expr*> args_):
                name(name_),args(args_){};
            std::string str() const
            {
                std::ostringstream out;
                out<<name<<"(";
                if (args.size() != 0 )
                {
                    for(int i=0;i<args.size()-1;++i)
                        out<<args[i]<<',';
                    std::cerr<<args.size();
                        out<<args[args.size()-1];
                }                    
                out<<")";
                return out.str();
            }
            
        private:
            std::string name;
            std::vector<Expr*> args;
        };
        
        class Stmt : public Printable
        {
        public:
            virtual std::string str() const 
            {
                return ";";
            }
        };
        
        class AssignStmt : public Stmt
        {
        public:
            AssignStmt(Identifier* idf_,Expr* expr_):
                idf(idf_),expr(expr_){};
            std::string str() const
            {
                std::ostringstream out;
                out<<idf;
                out<<"=";
                out<<expr;
                out<<";\n";
                return out.str();
            }
        private:
            Identifier* idf; // rvalue
            Expr* expr;//lvalue
        };
        class StandaloneExprStmt : public Stmt
        {
        public:
            StandaloneExprStmt(Expr* expr_):expr(expr_){};
            std::string str() const
            {
                return expr->str()+";\n";
            }
        private:
            Expr* expr;
        };
        class StmtBlock : public Stmt
        {
        public:
            StmtBlock(std::vector<Stmt*> stmts_):stmts(stmts_){};
            std::string str() const
            {
                std::ostringstream out;
                out<<"{\n";
                for(auto stmt: stmts)
                    out<<stmt;
                out<<"}\n";
                return out.str();
            }
        private:
            std::vector<Stmt*> stmts;
        };
        
        class IfStmt: public Stmt
        {
        public:
            IfStmt(Expr* condition_, Stmt* tstmt_, Stmt* fstmt_):
                condition(condition_),tstmt(tstmt_),fstmt(fstmt_){};
            std::string str() const
            {
                std::ostringstream out;
                out<<"if("<<condition<<")\n";
                out<<tstmt;
                out<<"\nelse\n";
                out<<fstmt;
                return out.str();
            }
        private:
            Expr* condition;
            Stmt* tstmt;
            Stmt* fstmt;
        };
        
        class WhileStmt : public Stmt
        {
        public:
            WhileStmt(Expr* condition_, Stmt* stmt_):
                condition(condition_),stmt(stmt_){};
            std::string str() const
            {
                std::ostringstream out;
                out<<"while("<<condition<<")\n"<<stmt;
                return out.str();
            }
        private:
            Expr* condition;
            Stmt* stmt;
        };
        
    }
}
#endif
