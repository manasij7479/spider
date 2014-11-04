#ifndef GRAPH_DISPLAY_HPP
#define GRAPH_DISPLAY_HPP
#include "Layout/Layout.hpp"
#include "graph/algorithm/collections.hpp"
#include <thread>
#include <SFML/Graphics.hpp>
#include <atomic>
#include "Display/GraphSprite.hpp"
#include <Event/Event.hpp>
namespace spider
{
    template<typename Graph>
    class Display
    {
    public:
        Display(GraphSprite<Graph>* gs, int sizex_, int sizey_ ) 
        {    
            keepOpen = true;
            sizex = sizex_;
            sizey = sizey_;
//             layout = l;
            gsprite = gs;
            thread = new std::thread(std::bind (&Display<Graph>::winThread, this));
//             layoutChanged = true;
            
        }
//         Display(int sizex_, int sizey_)
//         {
//             keepOpen = true;
//             sizex = sizex_;
//             sizey = sizey_;
//             gsprite = nullptr;
//             thread = new std::thread(std::bind (&Display<Graph>::winThread, this));
//         }
        void winThread()
        {
            sf::RenderWindow window(sf::VideoMode(sizex, sizey), "Display",sf::Style::None|sf::Style::Titlebar|sf::Style::Close);
            
            int moveFlag=0,noTicks;
            sf::Vector2f diff;
            sf::Vector2i initial;
            
//             setLayout(layout);
            gsprite->init(sizex,sizey);
            
            while (window.isOpen())
            {
//                 if (layoutChanged)
//                 {
//                     layoutChanged = false;
//                     sprite = getSprite(sizex, sizey);
//                 }
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
                        if(gsprite->within(sf::Vector2f(initial)))
                            moveFlag=1;
                        diff=sf::Vector2f(initial)-gsprite->getPosition();
                    }
                    if(event.type == sf::Event::MouseButtonReleased)
                        moveFlag=0;
                    if(event.type == sf::Event::MouseWheelMoved)
                    {
                        noTicks=event.mouseWheel.delta;
                        moveFlag=2;
                    }
                    if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                        moveFlag=3;
                }
                
                
                window.clear(sf::Color::White);
                sf::Sprite& sprite = gsprite->get();
                
//                 if (layout == nullptr)
//                     continue;
                
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
                    moveFlag=0;
                    sf::Vector2f finalPos;
                    sf::Vector2i initialPos=sf::Mouse::getPosition(window);
                    if(noTicks>0)
                    {
                        sprite.scale(1.2,1.2);
                        finalPos.x=1.2*(float)initialPos.x;
                        finalPos.y=1.2*(float)initialPos.y;
                    }
                    if(noTicks<0)
                    {
                        sprite.scale(0.8,0.8);
                        finalPos.x=0.8*(float)initialPos.x;
                        finalPos.y=0.8*(float)initialPos.y;
                    }
                    sprite.move((sf::Vector2f)initialPos-finalPos);
                    window.draw(sprite);
                }
                if(moveFlag == 3)                           //Fit-to-Page with Esc 
                {
                    sprite.setScale(1,1);
                    sprite.setPosition(0.0,0.0);
                    window.draw(sprite);
                    moveFlag=0;
                }
                
                window.display();
                if (!keepOpen)
                    window.close();
            }
        };
//         void initializeRenderTexture(int sizex=200,int sizey=200)
//         {
//             rendertexture.create(sizex,sizey);
//             rendertexture.clear(sf::Color::White);
//             rendertexture.setSmooth(true);
//         }
//         void drawVertices()
//         {
//             sf::CircleShape vertex(10,10);
//             vertex.setFillColor(sf::Color::Blue);
//             for(auto v : graph::VertexList(layout->getGraph()))
//             {
//                 Point p=layout->getVertex(v);
//                 vertex.setPosition(p.x,p.y);
//                 rendertexture.draw(vertex);
//             }
//         }
//         void drawEdges()
//         {
//             for (auto e : graph::EdgeList(layout->getGraph(), false))
//                     {
//                         Curve c=layout->getEdge(std::get<0>(e),std::get<1>(e));
//                         
//                         sf::Vertex line[] =
//                         {
//                             sf::Vertex(sf::Vector2f(c[0].x, c[0].y)),
//                             sf::Vertex(sf::Vector2f(c[1].x, c[1].y))
//                         };
//                         line[0].color=sf::Color::Black;
//                         line[1].color=sf::Color::Black;
//                         rendertexture.draw(line, 2, sf::Lines);
//                     }
//         }
//         sf::Sprite getSprite(int sizex,int sizey)
//         {
//             initializeRenderTexture(sizex,sizey);
//             drawVertices();
//             drawEdges();
//             sf::Sprite sp;
//             sp.setTexture(rendertexture.getTexture());
//             return sp;
//         }
//         void setLayout(Layout<Graph>* newLayout)
//         {
// //             float border = 50;
// //             layout = newLayout;
// //             Rect bounds = {{0 + border,0 + border},{sizex * 1.0f - border , sizey * 1.0f - border}};
// //             layout->generate(bounds);
//             layoutChanged = true;
//         }
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
//         Layout<Graph>* layout;
//         sf::RenderTexture rendertexture;
//         sf::Sprite sprite;
        GraphSprite<Graph>* gsprite;
        std::atomic<bool> keepOpen;
        std::thread *thread;
        int sizex, sizey;
//         bool layoutChanged;
    };
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