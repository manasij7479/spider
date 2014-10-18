#ifndef GRAPH_DISPLAY_HPP
#define GRAPH_DISPLAY_HPP
#include "Layout/Layout.hpp"
#include "graph/algorithm/collections.hpp"
#include <thread>
#include <SFML/Graphics.hpp>
#include <atomic>
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
                        {
                            window.close();
                            keepOpen = false;
                        }
                    }
                    window.clear(sf::Color::White);
                    for(auto v : graph::VertexList(g))
                    {
                        Point p = layout.getVertex(v);
                        c.setPosition(p.x,p.y);
                        window.draw(c);
                    }
                    for (auto e : graph::EdgeList(g, false))
                    {
                        Curve c=layout.getEdge(std::get<0>(e),std::get<1>(e));
                        
                        sf::Vertex line[] =
                        {
                            sf::Vertex(sf::Vector2f(c[0].x, c[0].y)),
                            sf::Vertex(sf::Vector2f(c[1].x, c[1].y))
                        };
                        line[0].color=sf::Color::Black;
                        line[1].color=sf::Color::Black;
                        window.draw(line, 2, sf::Lines);
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
        bool isOpen()
        {
            bool ret = keepOpen;
            return ret;
        }
        bool wait()
        {
            thread->join();
        }
    private:
        Layout<Graph>& layout;
        Graph& g;
        std::atomic<bool> keepOpen;
        std::thread *thread;
    };
}
#endif