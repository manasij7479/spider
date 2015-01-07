#ifndef SPIDER_USER_GRAPH
#define SPIDER_USER_GRAPH
#include <graph/graph.hpp>
#include <graph/util/generate.hpp>
#include <vector>
#include <string>
#include <functional>
#include <stdexcept>
#include <map>
#include <Runtime/UserType.hpp>
#include <graph/util/io.hpp>
namespace spider
{
    typedef std::function<graph::AdjacencyList<std::string,int>(std::vector<int>, int)> F;
    std::map<std::string, F> GraphNameMap = 
    {
        {"path", graph::gen::path},
        {"cycle", graph::gen::cycle},
        {"complete", graph::gen::complete},
        {"wheel", graph::gen::wheel},
        {"complete_bipartite", graph::gen::complete_bipartite},
        {"star", graph::gen::star},
        {"star_polygon", graph::gen::star_polygon},
        {"friendship", graph::gen::friendship},
        {"mobius_ladder", graph::gen::mobius_ladder},
        {"grid", graph::gen::grid},
        {"generalized_petersen", graph::gen::generalized_petersen},
        {"wagner", graph::gen::wagner},
        {"butterfly", graph::gen::butterfly},
        {"petersen", graph::gen::petersen},
        {"durer", graph::gen::durer},
        {"desargues", graph::gen::desargues},
        {"mobius_kantor", graph::gen::mobius_kantor},
        {"dodecahedron", graph::gen::dodecahedron},
        {"nauru", graph::gen::nauru}
    };
    class UserGraph : public UserType
    {
        typedef std::vector<std::string> Args;
        void assert_arg_size(const Args& args, int size)
        {
            if (args.size()!=size)
            throw std::runtime_error(
                "Argument size mismatch: Expected " 
                + std::to_string(size) 
                + " got "+std::to_string(args.size()));
        }
    public:
        typedef graph::AdjacencyList<std::string,int> Native;
//         UserGraph(bool directed = false):obj(new Native(directed)){};
//         UserGraph(Native *g):obj(g){}
        UserGraph(Args args) : UserType(UserType::Type::Graph)
        {
//             setCallback();
//             for (auto x: args)std::cout<<x<<'\t';
            if (args.empty())
            {
                obj = new Native(false);//undirected
            }
            else
            {
                std::vector<int> int_args;
                for (int i=1; i< args.size(); ++i)
                    int_args.push_back(std::stoi(args[i]));
                obj = new Native(GraphNameMap[args[0]](int_args, 1));
            }
//             else if (args[0] == "cycle")
//             {
//                 assert_arg_size(args, 2);
//                 int n = std::stoi(args[1]);
//                 obj = new Native(graph::gen::cycle({n}));
//             }
//             else
//             {
//                 //TODO:More generators, maybe set up a table?
//                 std::cout<<"NOT IMPLEMENTED"<<std::endl;
//             }
        }
        
        void eval(Args args)
        {
            if (args[0] == "insertVertex")
            {
                args.erase(args.begin());
                insertVertex(args);
            }
            else if (args[0] == "insertEdge")
            {
                args.erase(args.begin());
                insertEdge(args);
            }
            else if (args[0] == "removeVertex")
            {
                args.erase(args.begin());
                removeVertex(args);
            }
            else if (args[0] == "removeEdge")
            {
                args.erase(args.begin());
                removeEdge(args);
            }
            else if (args[0] == "show")
            {
                graph::displayGraph(*obj);
            }
            else throw std::runtime_error("Unsupported Operation.\n");
        }
        
        void insertVertex(Args args)
        {
            assert_arg_size(args, 1);
            obj->insertVertex(args[0]);
            changeCallback();
        }
        void removeVertex(Args args)
        {
            assert_arg_size(args, 1);
            obj->removeVertex(args[0]);
            changeCallback();
        }
        void insertEdge(Args args)
        {
            assert_arg_size(args, 3);
            obj->insertEdge(args[0], args[1], std::stoi(args[2]));
            changeCallback();
        }
        void removeEdge(Args args)
        {
            assert_arg_size(args, 2);
            obj->removeEdge(args[0], args[1]);
            changeCallback();
        }
        
        Native* getNativeObj(){return obj;} //DANGER: Callbacks won't work
        void setNativeObj(Native* obj_){obj = obj_; changeCallback();}
        void setCallback(std::function<void(void)> f){changeCallbacks.push_back(f);}
        
    private:
        Native* obj;
        void changeCallback(){for(auto&& f: changeCallbacks)f();}
        std::vector<std::function<void(void)>> changeCallbacks;
    };
}
#endif