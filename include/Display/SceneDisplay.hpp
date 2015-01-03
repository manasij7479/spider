#ifndef GRAPH_DISPLAY_HPP
#define GRAPH_DISPLAY_HPP
#include "Layout/Layout.hpp"
#include "graph/algorithm/collections.hpp"
#include <thread>
#include <SFML/Graphics.hpp>
#include <atomic>
#include "Display/SceneNode.hpp"
#include <Event/EventManager.hpp>
namespace spider
{
    class SceneDisplay
    {
    public:
        SceneDisplay(SceneNode* r, EventManager* em, int x, int y ): root(r),eventMgr(em), sizex(x),sizey(y)
        {
            keepOpen = true;
            eventMgr->registerCloseHandler(std::bind(&SceneDisplay::close, this));
            thread = new std::thread(std::bind (&SceneDisplay::winThread, this));
        }
        void winThread()
        {
            sf::RenderWindow window(sf::VideoMode(sizex, sizey), "Display", sf::Style::None|sf::Style::Titlebar|sf::Style::Close);
            while (window.isOpen())
            {
                window.clear(sf::Color::White);
                sf::Event event;
                while (window.pollEvent(event))
                {
                    if (event.type == sf::Event::MouseButtonPressed)
                        eventMgr->reportMouseClickEvent(event.mouseButton.x,event.mouseButton.y);
                    if (event.type == sf::Event::MouseMoved)
                        eventMgr->reportMovedEvent(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y);
                    if (event.type == sf::Event::MouseButtonReleased)
                        eventMgr->reportReleaseedEvent();
                    if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                        eventMgr->reportEscapeEvent();
                    if (event.type == sf::Event::MouseWheelMoved)
                        eventMgr->reportScrollEvent(event.mouseWheel.delta, event.mouseWheel.x, event.mouseWheel.y);
                    if (event.type == sf::Event::Closed)
                    {
                        window.close();
                        keepOpen = false;
                    }
                }
                root->draw(&window, vec2(0,0));
                window.display();
                if (!keepOpen)
                    window.close();
            }
        }
        void close()
        {
            keepOpen = false;
            thread->join();
        }
        bool isOpen()
        {
            bool ret = keepOpen;
            return ret;
        }
    private:
        SceneNode* root;
        EventManager* eventMgr;
        int sizex;
        int sizey;
        std::thread* thread;
        std::atomic<bool> keepOpen;
    };
    
    
}
#endif