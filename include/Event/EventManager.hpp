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
        typedef std::function<void(int, float, float)> viff;
        typedef std::function<void(void*)> vvp; // DANGER
        typedef vff MouseClickFunction;
        typedef vv CloseFunction;
    public:
        std::vector<MouseClickFunction> mouseClickHandlers;
        void registerMouseClickHandler(MouseClickFunction f)
        {
            mouseClickHandlers.push_back(f);
        }
        void reportMouseClickEvent(float x, float y)
        {
            for(auto& f: mouseClickHandlers)
                f(x,y);
        }
        
        std::vector<CloseFunction> closeHandlers;
        void registerCloseHandler(CloseFunction f)
        {
            closeHandlers.push_back(f);
        }
        void reportCloseEvent()
        {
            for(auto& f: closeHandlers)
                f();
        }
        
        std::vector<vff> movedHandlers;
        void registerMovedHandler(vff f)
        {
            movedHandlers.push_back(f);
        }
        void reportMovedEvent(float x,float y)
        {
            for(auto& f: movedHandlers)
                f(x,y);
        }
        
        std::vector<vv> releasedHandlers;
        void registerReleasedHandler(vv f)
        {
            releasedHandlers.push_back(f);
        }
        void reportReleaseedEvent()
        {
            for(auto& f: releasedHandlers)
                f();
        }
        
        std::vector<vv> escapeHandlers;
        void registerEscapeHandler(vv f)
        {
            escapeHandlers.push_back(f);
        }
        void reportEscapeEvent()
        {
            for(auto& f: escapeHandlers)
                f();
        }
        
        std::vector<viff> scrollHandlers;
        void registerScrollHandler(viff f)
        {
            scrollHandlers.push_back(f);
        }
        void reportScrollEvent( int ticks, float x, float y)
        {
            for(auto& f: scrollHandlers)
                f(ticks,x,y);
        }
        
        std::vector<vv> redrawHandlers;
        void registerRedrawHandler(vv f)
        {
            redrawHandlers.push_back(f);
        }
        void reportRedrawEvent()
        {
            for(auto& f: redrawHandlers)
                f();
        }

    };
}
#endif