#ifndef SPIDER_EVENT_EVENT_HPP
#define SPIDER_EVENT_EVENT_HPP
#include <functional>
#include <vector>
#include <Layout/Layout.hpp>
namespace spider
{
    //May need locks later, not sure
    class EventManager
    {
    private:
        typedef std::function<void(float,float)> vff;
        typedef std::function<void(void)> vv;
        typedef std::function<void(int, float, float)> viff;
        
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
        
        void registerMovedHandler(vff f)
        {
            movedHandlers.push_back(f);
        }
        void reportMovedEvent(float x,float y)
        {
            for(auto& f: movedHandlers)
                f(x,y);
        }
        
        void registerReleasededHandler(vv f)
        {
            releasedHandlers.push_back(f);
        }
        void reportReleaseedEvent()
        {
            for(auto& f: releasedHandlers)
                f();
        }
        
        void registerEscapeHandler(vv f)
        {
            escapeHandlers.push_back(f);
        }
        void reportEscapeEvent()
        {
            for(auto& f: escapeHandlers)
                f();
        }
        
        void registerScrollHandler(viff f)
        {
            scrollHandlers.push_back(f);
        }
        void reportScrollEvent( int ticks, float x, float y)
        {
            for(auto& f: scrollHandlers)
                f(ticks,x,y);
        }
    private:
        std::vector<MouseClickFunction> mouseClickHandlers;
        std::vector<CloseFunction> closeHandlers;
        std::vector<vff> movedHandlers;
        std::vector<vv> releasedHandlers;
        std::vector<vv> escapeHandlers;
        std::vector<viff> scrollHandlers;
    };
}
#endif