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
        Display(Layout<Graph>* l, int sizex_, int sizey_ ) 
        {    
            keepOpen = true;
            sizex = sizex_;
            sizey = sizey_;
            setLayout(l);
            
            auto winThread = [&](int sx, int sy)
            {
                sf::RenderWindow window(sf::VideoMode(sx, sy), "Display");
                sf::Sprite  sp = getSprite(sx,sy);
                
                while (window.isOpen())
                {
                    
                    if (layoutChanged)
                        sp=getSprite(sx,sy);
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
                    
                    window.draw(sp);
                    
                    window.display();
                    if (!keepOpen)
                        window.close();
                }
            };
            thread = new std::thread(winThread, sizex, sizey);
            
        }
        void initializeRenderTexture(int sizex=200,int sizey=200)
        {
            rendertexture.create(sizex,sizey);
            rendertexture.clear(sf::Color::White);
            rendertexture.setSmooth(true);
        }
        void drawVertices()
        {
            sf::CircleShape vertex(10,1000000);
            vertex.setFillColor(sf::Color::Blue);
            for(auto v : graph::VertexList(layout->getGraph()))
            {
                Point p=layout->getVertex(v);
                vertex.setPosition(p.x,p.y);
                rendertexture.draw(vertex);
            }
        }
        void drawEdges()
        {
            for (auto e : graph::EdgeList(layout->getGraph(), false))
                    {
                        Curve c=layout->getEdge(std::get<0>(e),std::get<1>(e));
                        
                        sf::Vertex line[] =
                        {
                            sf::Vertex(sf::Vector2f(c[0].x, c[0].y)),
                            sf::Vertex(sf::Vector2f(c[1].x, c[1].y))
                        };
                        line[0].color=sf::Color::Black;
                        line[1].color=sf::Color::Black;
                        rendertexture.draw(line, 2, sf::Lines);
                    }
        }
        sf::Sprite getSprite(int sizex,int sizey)
        {
            initializeRenderTexture(sizex,sizey);
            drawVertices();
            drawEdges();
            sf::Sprite sp;
            sp.setTexture(rendertexture.getTexture());
            layoutChanged = false;
            return sp;
        }
        void setLayout(Layout<Graph>* newLayout)
        {
            layout = newLayout;
            Rect bounds = {{0,0},{sizex * 1.0f,sizey * 1.0f}};
            layout->generate(bounds);
            layoutChanged = true;
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
        Layout<Graph>* layout;
        sf::RenderTexture rendertexture;
        std::atomic<bool> keepOpen;
        bool layoutChanged;
        std::thread *thread;
        int sizex, sizey;
    };
}
#endif