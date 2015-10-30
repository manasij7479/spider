#include "Compiler/Sema.hpp"
namespace spider
{
    std::string Sema::getReturnType(std::string f)
    {
        auto p = table.lookup(f);
        if (!p.first)
            throw std::runtime_error("Function: '"+f+"' does not exist.");
        
        if (p.second.getArgTypes().empty() && p.second.getType() == "func")
        {
            return "any";
        }
        if (!p.second.isFunction())
            throw std::runtime_error("'"+f+"' is not a function.");
        
        return p.second.getArgTypes()[0].first;
    }
    std::vector<std::pair<std::string, std::string>> Sema::getArgTypeList(std::string f)
    {
        auto p = table.lookup(f);
        if (!p.first)
            throw std::runtime_error("Function: '"+f+"' does not exist.");
        if (p.second.getArgTypes().empty() && p.second.getType() == "func")
        {
            return {};
        }
        if (!p.second.isFunction())
            throw std::runtime_error("'"+f+"' is not a function.");
        auto&& result = p.second.getArgTypes();
        result.erase(result.begin());
        return result;
    }
    
    void Sema::output(std::string s, bool endl)
    {
        std::ostream& out = *output_stack.back();
        out << s;
        if (endl)
            out << std::endl;
    }
    std::string convert_to_rpn(std::string input)
    {
        static std::map<char, std::pair<int, bool>> op_table = 
        {
            {'+', {0, false}},
            {'-', {0, false}},
            {'*', {1, false}},
            {'/', {1, false}},
            {'%', {1, false}},
            {'^', {2, true }},
        };
        std::string result;
        std::vector<char> ops;
        auto it = op_table.begin();
        for (int i = 0; i < input.size(); ++i)
        {
            if (std::isdigit(input[i]))
                result += input[i];
            else if ((it = op_table.find(input[i])) != op_table.end())
            {
                while(!ops.empty())
                {
                    char sop = ops.back();
                    if ( it->second.second == true && op_table[sop].first > it->second.first)
                    {
                        result+=sop;
                        ops.pop_back();
                    }
                    if ( it->second.second == false  && op_table[sop].first >= it->second.first)
                    {
                        result+=sop;
                        ops.pop_back();
                    }
                    else break;
                }
                ops.push_back(it->first);
            }
            else if (input[i] == '(')
                ops.push_back('(');
            else if (input[i] == ')')
            {
                while(true)
                {
                    if (ops.empty())
                        throw std::runtime_error("Mal formed infix expression in input.");
                    char c = ops.back();
                    ops.pop_back();
                    if (c == '(')
                        break;
                    else result += c;
                }
            }
            else throw std::runtime_error(std::string("Bad Operator in special expression: ").append(1, input[i]));
        }
        while(!ops.empty())
        {
            char c = ops.back();
            if (c == '(')
                throw std::runtime_error("Mal formed infix expression in input.");
            result += ops.back();
            ops.pop_back();
        }
        return result;
        
    }
    std::pair<std::string, Type> Sema::process(SpecialExpr* ce)
    {
        std::string control = ce->getSpecialToken()->getData();
        control = control.substr(1, control.length()-2);
//             std::istringstream in(control.substr(1, control.length()-2));
        std::vector<std::pair<std::string, Type>> pargs;
        for (auto expr : ce->getArgs()->getData())
            pargs.push_back(process(expr));
        if (pargs.empty())
            throw std::runtime_error("Arg List Can not be empty,");
        control=convert_to_rpn(control);
        //generate code for rpn
        std::string modifier  = (pargs[0].second.getType() == "float" ? "f":"");
        std::vector<std::pair<std::string, Type>> opn;
        for(int i = 0; i < control.length(); ++i)
        {
            if (std::isdigit(control[i]))
                opn.push_back(pargs[control[i]-'0']);
            else 
            {
                //todo size and type check
                auto y = opn.back(); opn.pop_back();
                auto x = opn.back(); opn.pop_back();
                std::string name = table.getNewName(x.second);
                switch(control[i])
                {
                    case '+':
                        output("let " + name + " add"+ modifier+" "+x.first+" "+y.first);
                        break;
                    case '-':
                        output("let " + name + " sub"+ modifier+" "+x.first+" "+y.first);
                        break;
                    case '*':
                        output("let " + name + " mul"+ modifier+" "+x.first+" "+y.first);
                        break;
                    case '/':
                        output("let " + name + " div"+ modifier+" "+x.first+" "+y.first);
                        break;
                    case '%':
                        output("let " + name + " mod"+ modifier+" "+x.first+" "+y.first);
                        break;
                    case '^':
                        output("let " + name + " pow"+ modifier+" "+x.first+" "+y.first);
                        break;
                    default: throw std::runtime_error(std::string("Bad operator in special expression: ").append(1, control[i]));
                }
                opn.push_back({name, x.second});
            }
        }
        
        return opn[0];
    }
    std::pair<std::string, Type> Sema::process(CallExpr* ce, bool assign)
    {
        std::ostringstream os;
        std::string fname = ce->getCallee()->getToken()->data;
        std::string s = table.getNewName(getReturnType(fname));
        auto&& args = getArgTypeList(fname);

        if (getReturnType(fname) != "void" && assign == true)
            os << "let " << s << ' ';
        
        os << fname << ' ';

        if ( args.size() != 0 && args.size() != ce->getArgs()->getData().size())
            throw std::runtime_error("Argument size mismatch, expected '"+std::to_string(args.size())+"' got '"+std::to_string(ce->getArgs()->getData().size()));
        for(int i = 0 ; i < ce->getArgs()->getData().size(); ++i)
        {
//                 ce->getArgs()->getData()[i]->dump();
            auto p = process(ce->getArgs()->getData()[i]);
            
            std::string argtype = p.second.getType();
            if (args.size() != 0 && Type(args[i].first).isCompatible(argtype) == false)
            {
//                     std::cerr << "DEBUG" << args[i].first << ','<< p.first << ',' << p.second.getType() << ','<< std::endl;
                throw std::runtime_error("Type Mismatch, expected '"+args[i].first+"' got '"+p.second.getType());
            }
            os << p.first << ' ';
        }
        output(os.str());
        return {s, getReturnType(ce->getCallee()->getToken()->data)};
    }
    std::pair<std::string, Type> Sema::process(Expr* e)
    {
        switch (e->type)
        {
            case EType::Id : 
            {
                auto s = static_cast<IdExpr*>(e)->getToken()->data;
                return {s, table.lookup(s).second};
            }
            case EType::Int : return {"i"+std::to_string(static_cast<IntLiteralExpr*>(e)->getToken()->data), Type("int")};
            case EType::Float : return {"f"+std::to_string(static_cast<FloatLiteralExpr*>(e)->getToken()->data), Type("float")};
            case EType::String : return {static_cast<StringLiteralExpr*>(e)->getToken()->data,Type("string")};
            case EType::Bool : return {static_cast<BoolLiteralExpr*>(e)->getToken()->data,Type("bool")};
            case EType::Call: return process(static_cast<CallExpr*>(e));
            case EType::Special: return process(static_cast<SpecialExpr*>(e));
        }
    }
    std::string Sema::convert_into_function(Expr* e) // returns function name
    {
        std::ostringstream temp;
        
        output_stack.push_back(&temp);
        auto p = process(e);
        output_stack.pop_back();
        std::vector<std::pair<std::string, std::string>> type;
        type.push_back({p.second.getType(), p.first});
        std::string fname = table.getNewName(Type(type));
        std::string result = table.getNewName(Type(p.second.getType()));
        
        output("function " + fname + " " + result + " " + p.second.getType());
        output("{");
        output(temp.str(), false);
        output("let " + result + " " +  p.first);
        output("}");
        return fname;
    }
    void Sema::process(ImportStmt* imp)
    {
        std::string filename = imp->getStr()->getToken()->data;
        yyin = nullptr;
        yyin = std::fopen(filename.substr(1, filename.length()-2).c_str(), "r");
        if (!yyin)
            throw std::runtime_error("File "+filename+" not found.");
        pushState();
        yylex();
        insertToken(new EOFToken);
        auto p = ZeroOrMore(parseStmt)(0);

        if (!p)
            std::cerr << p.getError() << std::endl;
        else
        {
    //         std::cout << "Parsed" << std::endl;
    //         if (p.get() != nullptr)
    //             p.get()->dump();
            ASTNodeVector* v = static_cast<ASTNodeVector*>(p.get());
            std::vector<ASTNode*> data = v->getData();
            for (auto node : data)
            {
    //             static_cast<spc::Stmt*>(node)->dump();
                this->process(static_cast<Stmt*>(node));
            }
        }
        popState();
    }
    void Sema::process(FunctionPrototype* fp, bool codegen)
    {
        std::ostringstream out;
        out << "function ";
        std::string fname = fp->getName()->getToken()->data;
        std::string rettype, retname;
        if (fp->getReturnArg() != nullptr)
            rettype = fp->getReturnArg()->getTypeName()->getToken()->data;
        else rettype = "any";
        std::vector<std::pair<std::string, std::string>> mapdata;
        out << fname << " ";
        if (fp->getReturnArg() != nullptr)
            retname = fp->getReturnArg()->getName()->getToken()->data;
        else
                retname = "_placeholder"; 
        out << retname << " ";
        out << rettype << " ";
        
        mapdata.push_back({rettype, retname});
        for (FunctionArg* arg : fp->getArgs())
        {
            std::string argtype = arg->getTypeName()->getToken()->data;
            out << arg->getName()->getToken()->data << " ";
            out << argtype << " ";
            mapdata.push_back({argtype, arg->getName()->getToken()->data});
        }
        table.insert(fname, Type(mapdata));
        if (codegen)
        {
            output(out.str());
            for (auto p: getArgTypeList(fname))
            {
//                     std::cerr << "INSERT:" << p.second << ','<<p.first<<std::endl;
                table.insert(p.second, Type(p.first));
            }
        }
        
    }
    void Sema::process(IfStmt* ifs)
    {
        //anything else?
        Expr* e = ifs->getCondition();
        auto p = process(e);
        //check if p.second is bool
        output("if " + p.first);
        Stmt* tb = ifs->getTrueBlock();
        process(tb);
        Stmt* fb = ifs->getFalseBlock();
        if(fb)
        {
            output("not " + p.first);
            output("if _");
            process(fb);
        }
        
    }
    void Sema::process(Stmt* s)
    {
        switch(s->type)
        {
            case SType::Decl: process(static_cast<DeclStmt*>(s)); break;
            case SType::Assign: process(static_cast<AssignStmt*>(s)); break;
            case SType::If: process(static_cast<IfStmt*>(s)); break;
            case SType::While: process(static_cast<WhileStmt*>(s)); break;
            case SType::Block: process(static_cast<StmtBlock*>(s)); break;
            case SType::FDef: process(static_cast<FunctionDefinition*>(s)); break;
            case SType::FDecl: process(static_cast<FunctionDeclaration*>(s)); break;
            case SType::VCall: process(static_cast<VoidCallStmt*>(s)); break;
            case SType::Import: process(static_cast<ImportStmt*>(s)); break;
        }
    }
    void Sema::process(DeclStmt* ds)
    {
        IdExpr* id = ds->getAssignStmt()->getLvalue();
        auto p = process(ds->getAssignStmt()->getRvalue());
//             m_TypeMap[id->getToken()->data] = p.second;
        table.insert(id->getToken()->data, p.second);
        output("let "+ id->getToken()->data + " " + p.first);
    }
    void Sema::process(AssignStmt* as)
    {
        IdExpr* id = as->getLvalue();
        auto p = process(as->getRvalue());
        //TODO: Write better error message
        if (table.lookup(id->getToken()->data).second != p.second)
            throw std::runtime_error("Type mismatch in assign statement");
        output("assign "+ id->getToken()->data + " " + p.first); 
    }
    void Sema::process(StmtBlock* b)
    {
        output("{");
        for (auto s : b->getData())
            process(s);
        output("}");
    }
    void Sema::process(WhileStmt* ws)
    {
        Expr* e = ws->getCondition();
        std::string s = convert_into_function(e);
        output("while " + s);
        process(ws->getBlock());
    }
}