#ifndef SPIDER_EVENT_EVENT_HPP
#define SPIDER_EVENT_EVENT_HPP
#include <functional>
#include <vector>
namespace spider
{
    class EventManager
    {
    private:
        typedef std::function<void(float,float)> MouseClickFunction;
    public:
        void registerMouseClickHandler(MouseClickFunction f)
        {
            mouseClickHandlers.push_back(f);
        }
        void reportMouseClickEvent(float x, float y)
        {
            for(auto& f: mouseClickHandlers)
                f(x,y);
        }
    private:
        std::vector<std::function<void(float,float)>> mouseClickHandlers;
    };
}
#endif