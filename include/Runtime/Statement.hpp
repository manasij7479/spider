#ifndef SPIDER_RUNTIME_STATEMENT_HPP
#define SPIDER_RUNTIME_STATEMENT_HPP
#include <vector>
#include <map>
#include <sstream>
namespace spider
{
    class Statement
    {
    public:
        Statement(std::istream& in)
        {
            do standalone = split_get(in);
            while(standalone.size() == 0);
            
            if (standalone[0] == "{")
            {
                block = true;
                while (true)
                {
                    char close;
                    in >> close;
                    if (close == '}')
                    {
                        //maybe get the whole line here?
                        break;
                    }
                    else
                    {
                        in.putback(close);
                        inner.push_back(new Statement(in));
                    }
                }
            }
            else
            {
                block = false;
            }
            
        }
        bool isBlock()
        {
            return block;
        }
        std::vector<std::string> getSingle()
        {
            return standalone;
        }
        std::vector<Statement*> getBlock()
        {
            return inner;
        }
        void print(std::ostream& out, int tab = 0)
        {
            int t = tab;
            if (isBlock() == false)
            {
                while(t--)
                    out<<"  ";
                for (auto x : standalone)
                    out << x<<' ';
                out << std::endl;
            }
            else
            {
                int u = t;
                while(t--)
                    out<<"  ";
                out << "{\n";
                for(auto s : inner)
                    s->print(out, tab+1);
                while(u--)
                    out<<"  ";
                out << "}\n";
            }
        }
    private:
        std::vector<std::string> split_get(std::istream& in)
        {
            std::string line;
            std::getline(in, line);
            std::istringstream instr(line);
            std::vector<std::string> result;
            std::string temp;
            while(instr >> temp)
                result.push_back(temp);
            return result;
        }
        bool block;
        std::vector<Statement*> inner;
        std::vector<std::string> standalone;
    };
    
}
#endif