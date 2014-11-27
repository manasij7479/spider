#ifndef SPIDER_USER_GRAPH
#define SPIDER_USER_GRAPH
#include <graph/graph.hpp>
#include <vector>
#include <string>
#include <functional>
namespace spider
{
    class UserGraph
    {
    public:
        UserGraph(bool directed = false):obj(directed){setCallback();};
        
        UserGraph(std::vector<std::string> opts){setCallback();}//TODO 
        
        
        
        graph::AdjacencyList<std::string, int>* getNativeObj(){return &obj;} //DANGER: Callbacks won't work
        void setNativeObj(graph::AdjacencyList<std::string, int>* obj_){obj = *obj_; changeCallback();}
        void setCallback(std::function<void(void)> f = [](){}){changeCallback = f;}
    private:
        graph::AdjacencyList<std::string,int> obj;
        std::function<void(void)> changeCallback;
    };
}
#endif