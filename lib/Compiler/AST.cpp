#include "Compiler/AST.hpp"
#include "Compiler/Sema.hpp"
namespace spc
{
    ASTNode::ASTNode()
    {
    }
    void ASTNode::dump(int tab, std::ostream& out)
    {
        tabs(tab, out);
        out<<"<EMPTY NODE>\n";
    }
    void ASTNodeVector::dump(int tab, std::ostream& out)
    {
        tabs(tab, out);
        out << "Node Vector\n";
        for (auto node : data)
            if(node != nullptr)
                node->dump(tab+1, out);
            else
            {
                tabs(tab+1, out);
                out << "NULL\n";
            }
    }
    void IdExpr::dump(int tab, std::ostream& out)
    {
        tabs(tab, out);
        out << "Identifier: " << id->data << "\n";
    }
    
    void IntLiteralExpr::dump(int tab, std::ostream& out)
    {
        tabs(tab, out);
        out << "Int Literal: " << i->data << "\n";
    }
    
    void StringLiteralExpr::dump(int tab, std::ostream& out)
    {
        tabs(tab, out);
        out << "String Literal: " << s->data << "\n";
    }
    
    void ExprList::dump(int tab, std::ostream& out)
    {
        tabs(tab, out);
        out << "Expression List\n";
        for (auto node : data)
            if(node)
                node->dump(tab+1, out);
            else
            {
                tabs(tab+1);
                out << "NULL" << std::endl;
            }
    }
    
    void CallExpr::dump(int tab, std::ostream& out)
    {
        tabs(tab, out);
        out << "Prefix Call Expression\n";
        fname->dump(tab+1, out);
        args->dump(tab+1, out);
    }
    
    void AssignStmt::dump(int tab, std::ostream& out)
    {
        tabs(tab, out);
        out << "AssignStmt\n";
        tabs(tab, out);
        out << "Lvalue\n";
        lvalue->dump(tab+1, out);
        tabs(tab, out);
        out << "Rvalue\n";
        rvalue->dump(tab+1, out);
    }
    
    void DeclStmt::dump(int tab, std::ostream& out)
    {
        tabs(tab, out);
        out << "DeclStmt\n";
        stmt->dump(tab+1, out);
    }
    
    void IfStmt::dump(int tab, std::ostream& out)
    {
        tabs(tab, out);
        out << "IfStmt\n";
        condition->dump(tab+1, out);
        trueblock->dump(tab+1, out);
        if (falseblock)
            falseblock->dump(tab+1, out);
    }
    
    void WhileStmt::dump(int tab, std::ostream& out)
    {
        tabs(tab, out);
        out << "WhileStmt\n";
        condition->dump(tab+1, out);
        block->dump(tab+1, out);
    }
    
    void StmtBlock::dump(int tab, std::ostream& out)
    {
        tabs(tab, out);
        out << "StmtBlock\n";
        for (auto s : data)
            s->dump(tab+1, out);
    }
    
    void TypeDefinition::dump(int tab, std::ostream& out)
    {
        tabs(tab, out);
        out << "TypeDefinition\n";
        tabs(tab, out);
        if (id)
            id->dump(tab+1, out);
        else
        {
            tabs(tab);
            out << "Array: " << is_array<<"\n";
            for(auto td: data)
            {
                td->dump(tab+1, out);
            }
        }
    }
    
    void TypeDefinitionStmt::dump(int tab, std::ostream& out)
    {
        tabs(tab, out);
        out << "TypeDefinitionStmt\n";
        id->dump(tab+1, out);
        def->dump(tab+1, out);
    }
    
    FunctionArg::FunctionArg(IdExpr* name_, IdExpr* type_) : name(name_), type(type_)
    {
        
    }

    void FunctionArg::dump(int tab, std::ostream& out)
    {
        tabs(tab, out);
        out << "FunctionArg\n";
        name->dump(tab+1, out);
        type->dump(tab+1, out);
    }

    FunctionPrototype::FunctionPrototype(IdExpr* id_, FunctionArg* ret_, std::vector< FunctionArg* > args_): id(id_), ret(ret_), args(args_)
    {

    }
    
    void FunctionPrototype::dump(int tab, std::ostream& out)
    {
        tabs(tab, out);
        out << "FunctionProto\n";
        if (ret != nullptr)
            ret->dump(tab+1, out);
        else 
        {
            tabs(tab+1, out);
            out << "VOID\n";
        }
        for (auto arg: args)
            arg->dump(tab+1, out);
    }    
    FunctionDefinition::FunctionDefinition(FunctionPrototype* proto_, StmtBlock* block_): Stmt(SType::FDef), proto(proto_), block(block_)
    {

    }
    void FunctionDefinition::dump(int tab, std::ostream& out)
    {
        tabs(tab, out);
        out << "FunctionDef\n";
        proto->dump(tab+1, out);
        block->dump(tab+1, out);
    }

    void FunctionDeclaration::dump(int tab, std::ostream& out)
    {
        tabs(tab, out);
        out << "FunctionDecl\n";
        proto->dump(tab+1, out);
    }
    FunctionDeclaration::FunctionDeclaration(FunctionPrototype* proto_) : Stmt(SType::FDecl), proto(proto_)
    {

    }

    VoidCallStmt::VoidCallStmt(CallExpr* c): Stmt(SType::VCall), expr(c) 
    {

    }

    void VoidCallStmt::dump(int tab, std::ostream& out)
    {
        tabs(tab, out);
        out << "VoidCallStmt\n";
        expr->dump(tab+1, out);
    }

    
    void ImportStmt::dump(int tab, std::ostream& out)
    {
        tabs(tab, out);
        out << "ImportStmt\n";
        str->dump(tab+1, out);
    }


    
    TypeDefinitionStmt::TypeDefinitionStmt(IdExpr* i, TypeDefinition* td):Stmt(SType::Type), id(i), def(td)
    {
//         sema->process(this);
    }
    
    AssignStmt::AssignStmt(IdExpr* lv, Expr* rv):Stmt(SType::Assign), lvalue(lv), rvalue(rv)
    {
//         sema->process(this);
    }
    
    DeclStmt::DeclStmt(AssignStmt* as):Stmt(SType::Decl),stmt(as)
    {
//         sema->process(this);
    }
    
    IfStmt::IfStmt(Expr* c, Stmt* t, Stmt* f):Stmt(SType::If), condition(c), trueblock(t), falseblock(f)
    {
//         sema->process(this);
    }
    
    WhileStmt::WhileStmt(Expr* c, Stmt* b):Stmt(SType::While), condition(c), block(b)
    {
//         sema->process(this);
    }
    
    void FloatLiteralExpr::dump(int tab, std::ostream& out)
    {
        tabs(tab, out);
        out << "Float Literal: " << f->data << "\n";
    }

    
    void tabs(int t, std::ostream& out)
    {
        while(t--)
            out << '\t';
    }
    void SpecialExpr::dump(int tab, std::ostream& out)
    {
        tabs(tab, out);
        out << "Special Expression\n";
        sp->dump(tab+1, out);
        args->dump(tab+1, out);
    }
    void SpecialTokenNode::dump(int tab, std::ostream& out)
    {
        tabs(tab+1, out);
        out << "SpecialToken:" << sp->data << "\n";
    }
    void BoolLiteralExpr::dump(int tab, std::ostream& out)
    {
        tabs(tab, out);
        out << "Bool Literal\n";
        tabs(tab+1, out);
        out << sym->data << "\n";
    }

}