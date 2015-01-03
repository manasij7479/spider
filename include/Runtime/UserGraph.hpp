#ifndef SPIDER_USER_GRAPH
#define SPIDER_USER_GRAPH
#include <graph/graph.hpp>
#include <graph/util/generate.hpp>
#include <vector>
#include <string>
#include <functional>
#include <stdexcept>
namespace spider
{
    class UserGraph
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
        UserGraph(bool directed = false):obj(new Native(directed)){};
        UserGraph(Native *g):obj(g){}
        UserGraph(Args args)
        {
//             setCallback();
//             for (auto x: args)std::cout<<x<<'\t';
            if (args.empty())
            {
                obj = new Native(false);//undirected
            }
            else if (args[0] == "cycle")
            {
                assert_arg_size(args, 2);
                int n = std::stoi(args[1]);
                obj = new Native(graph::gen::cycle(n));
            }
            else
            {
                //TODO:More generators, maybe set up a table?
                std::cout<<"NOT IMPLEMENTED"<<std::endl;
            }
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
        void setCallback(std::function<void(void)> f){changeCallback = f;}
        
    private:
        Native* obj;
        std::function<void(void)> changeCallback;
    };
}
#endif