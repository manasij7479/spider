#ifndef GRAPH_DISPLAY_HPP
#define GRAPH_DISPLAY_HPP
#include "Layout/Layout.hpp"
#include <thread>
#include <SFML/Graphics.hpp>
namespace spider
{
    template<typename Graph>
    class Display
    {
    public:
        Display(Layout<Graph>& l, int sizex, int sizey ):layout(l), g(l.getGraph())
        {
            Rect bounds = {{0,0},{sizex * 1.0f,sizey * 1.0f}};
            layout.generate(bounds);
            keepOpen = true;
                        
            auto winThread = [&](int sx, int sy)
            {
                sf::RenderWindow window(sf::VideoMode(sx, sy), "Display");
                sf::CircleShape c(3,10);
                c.setFillColor(sf::Color::Blue);
                
                while (window.isOpen())
                {
                    sf::Event event;
                    while (window.pollEvent(event))
                    {
                        // "close requested" event: we close the window
                        if (event.type == sf::Event::Closed)
                            window.close();
                    }
                    window.clear(sf::Color::White);
                    for(auto x=g.begin(); x!=g.end(); ++x)
                    {
                        Point p = layout.getVertex(x->first);
                        c.setPosition(p.x,p.y);
                        window.draw(c);
                    }
                    window.display();
                    if (!keepOpen)
                        window.close();
                }
            };
            thread = new std::thread(winThread, sizex, sizey);
            
        }
        void close()
        {
            keepOpen = false;
            thread->join();
        }
    private:
        Layout<Graph>& layout;
        Graph& g;
        bool keepOpen;
        std::thread *thread;
    };
}
#endif