#ifndef SPIDER_EVENT_EVENT_HPP
#define SPIDER_EVENT_EVENT_HPP
#include <functional>
#include <vector>
namespace spider
{
    //May need locks later, not sure
    class EventManager
    {
    private:
        typedef std::function<void(float,float)> vff;
        typedef std::function<void(void)> vv;
        
        typedef vff MouseClickFunction;
        typedef vv CloseFunction;
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
        
        void registerCloseHandler(CloseFunction f)
        {
            closeHandlers.push_back(f);
        }
        void reportCloseEvent()
        {
            for(auto& f: closeHandlers)
                f();
        }
    private:
        std::vector<MouseClickFunction> mouseClickHandlers;
        std::vector<CloseFunction> closeHandlers;
    };
}
#endif