#ifndef SPIDER_USER_GRAPH
#define SPIDER_USER_GRAPH
#include <graph/graph.hpp>
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
        UserGraph(bool directed = false):obj(directed){setCallback();};
        
        UserGraph(Args opts){setCallback();}//TODO 
        
        void insertVertex(Args args)
        {
            assert_arg_size(args, 1);
            obj.insertVertex(args[0]);
            changeCallback();
        }
        void removeVertex(Args args)
        {
            assert_arg_size(args, 1);
            obj.removeVertex(args[0]);
            changeCallback();
        }
        void insertEdge(Args args)
        {
            assert_arg_size(args, 3);
            obj.insertEdge(args[0], args[1], std::stoi(args[2]));
            changeCallback();
        }
        void removeEdge(Args args)
        {
            assert_arg_size(args, 2);
            obj.removeEdge(args[0], args[1]);
            changeCallback();
        }
        
        graph::AdjacencyList<std::string, int>* getNativeObj(){return &obj;} //DANGER: Callbacks won't work
        void setNativeObj(graph::AdjacencyList<std::string, int>* obj_){obj = *obj_; changeCallback();}
        void setCallback(std::function<void(void)> f = [](){}){changeCallback = f;}
        
    private:
        graph::AdjacencyList<std::string,int> obj;
        std::function<void(void)> changeCallback;
    };
}
#endif