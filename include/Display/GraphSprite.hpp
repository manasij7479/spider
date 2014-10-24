#ifndef SPIDER_GRAPH_SPRITE
#define SPIDER_GRAPH_SPRITE
#include "SpiderSprite.hpp"
#include "graph/algorithm/collections.hpp"
namespace spider
{
    template <typename Graph>
    class GraphSprite : public Sprite
    {
    public:
        GraphSprite(Layout<Graph>* l, int x, int y)
        {
            layout = l;
            init(x,y);
        }
        GraphSprite(Layout<Graph>* l)
        {
            layout = l;
            //init NOT called, size has to be set later
        }
        void init(int x, int y)
        {
            sizex = x;
            sizey = y;
            float border = 50;
            Rect bounds = {{0 + border,0 + border},{sizex * 1.0f - border , sizey * 1.0f - border}};
            layout->generate(bounds);
            initializeRenderTexture(sizex,sizey);
            drawEdges();
            drawVertices();
            sp.setTexture(rendertexture.getTexture());
        }
        bool within(float x, float y)
        {
            return sp.getGlobalBounds().contains(x,y);
        }
        sf::Sprite& get() // set up locks
        {
            return sp;
        }
        void initializeRenderTexture(int sizex=200,int sizey=200)
        {
            rendertexture.create(sizex,sizey);
            rendertexture.clear(sf::Color::White);
            rendertexture.setSmooth(true);
        }
        void drawVertices()
        {
            sf::CircleShape vertex(5,10);
            vertex.setFillColor(sf::Color::Blue);
            vertex.setOrigin(vertex.getOrigin().x+vertex.getRadius(),vertex.getOrigin().y+vertex.getRadius());
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
        void setLayout(Layout<Graph>* l)
        {
            layout = l;
            init(sizex,sizey);
        }
    private:
        sf::Sprite sp;
        sf::RenderTexture rendertexture;
        int sizex, sizey;
        bool layoutChanged;
        Layout<Graph>* layout;
        
    };
}
#endif