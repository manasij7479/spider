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
            layout = l;
            thread = new std::thread(std::bind (&Display<Graph>::winThread, this));
            
        }
        Display(int sizex_, int sizey_)
        {
            keepOpen = true;
            sizex = sizex_;
            sizey = sizey_;
            layout = nullptr;
            thread = new std::thread(std::bind (&Display<Graph>::winThread, this));
        }
        void winThread()
        {
            sf::RenderWindow window(sf::VideoMode(sizex, sizey), "Display");
            
            int moveFlag=0,noTicks;
            sf::Vector2f diff;
            sf::Vector2i initial;
            
            setLayout(layout);
            
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
//                     if (event.type == sf::Event::Resized)
//                     {
//                         std::cout << event.size.height << ' '<<event.size.width <<std::endl;
//                         sizex = event.size.width;
//                         sizey = event.size.height;
//                         setLayout(layout);
//                     }
                    if(event.type == sf::Event::MouseButtonPressed)
                    {
                        initial=sf::Mouse::getPosition(window);
                        if(sprite.getGlobalBounds().contains(sf::Vector2f(initial)))
                            moveFlag=1;
                        diff=sf::Vector2f(initial)-sprite.getPosition();
                    }
                    if(event.type == sf::Event::MouseButtonReleased)
                        moveFlag=0;
                    if(event.type == sf::Event::MouseWheelMoved)
                    {
                        noTicks=event.mouseWheel.delta;
                        moveFlag=2;
                    }
                }
                
                
                window.clear(sf::Color::White);
                
                if (layout == nullptr)
                    continue;
                
                if(moveFlag == 0)
                    window.draw(sprite);

                if(moveFlag == 1)
                {
                    if(sf::Mouse::getPosition(window).x>0&&sf::Mouse::getPosition(window).y>0&&sf::Mouse::getPosition(window).x<sizex&&sf::Mouse::getPosition(window).y<sizey)
                        sprite.setPosition(sf::Vector2f(sf::Mouse::getPosition(window))-diff);
                    window.draw(sprite);
                }
                if(moveFlag == 2)                      //Zoom in for upward scroll & vice-versa at mouse position
                {
                    sprite.setOrigin((sf::Vector2f)sf::Mouse::getPosition(window));
                    if(noTicks<0)
                        sprite.scale(0.5,0.5);
                    if(noTicks>0)
                        sprite.scale(2.0,2.0);
                    window.draw(sprite);
                    moveFlag=0;
                }
                
                window.display();
                if (!keepOpen)
                    window.close();
            }
        };
        void initializeRenderTexture(int sizex=200,int sizey=200)
        {
            rendertexture.create(sizex,sizey);
            rendertexture.clear(sf::Color::White);
            rendertexture.setSmooth(true);
        }
        void drawVertices()
        {
            sf::CircleShape vertex(10,10);
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
            return sp;
        }
        void setLayout(Layout<Graph>* newLayout)
        {
            float border = 50;
            layout = newLayout;
            Rect bounds = {{0 + border,0 + border},{sizex * 1.0f - border , sizey * 1.0f - border}};
            layout->generate(bounds);
            sprite = getSprite(sizex,sizey);
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
        sf::Sprite sprite;
        std::atomic<bool> keepOpen;
        std::thread *thread;
        int sizex, sizey;
    };
}
#endif