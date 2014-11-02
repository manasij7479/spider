#ifndef SPIDER_GRAPH_SPRITE
#define SPIDER_GRAPH_SPRITE
#include "SpiderSprite.hpp"
#include "SceneGraph.hpp"
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
        bool within(sf::Vector2f p)
        {
            return sp.getGlobalBounds().contains(p);
        }
        sf::Vector2f getPosition()
        {
            return sp.getPosition();
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

    template<typename Graph>
    class GraphSpriteObject // Will be renamed after the above class is discarded
    : public Drawable
    {
    public:
        GraphSpriteObject(Layout<Graph>* l, int x, int y) // x,y are no longer window sizes. local bounds are {(0,0),(x,y)}
        {
            layout = l ;
            init(x,y);
        }
        void init(int x, int y)
        {
            sizex = x;
            sizey = y;
            float border = 0;
            Rect bounds = {{0 + border,0 + border},{sizex * 1.0f - border , sizey * 1.0f - border}};
            layout->generate(bounds);
            generateEdgeArray();
            generateVertexArray();
        }
    void draw(sf::RenderWindow* win, vec2 offset)
    {
        sf::Transform translate;
        translate.translate(offset.x,offset.y);
        sf::RenderStates state(translate);
        win->draw(edgeArray.data(),edgeArray.size(), sf::Lines, state);
        sf::Texture tex;
        tex.loadFromFile("resource/vertex.png");
        state.texture = &tex;
        win->draw(vertexArray.data(), vertexArray.size(), sf::Quads, state);
        
        
    }
    void generateVertexArray()
    {
        vertexArray.clear();
        for(auto v : graph::VertexList(layout->getGraph()))
        {
            Point p=layout->getVertex(v);
            sf::Vertex quad[4];
            
            quad[0]= sf::Vertex(sf::Vector2f(p.x - 10, p.y - 10));
            quad[1]= sf::Vertex(sf::Vector2f(p.x - 10, p.y + 10));
            quad[2]= sf::Vertex(sf::Vector2f(p.x + 10, p.y + 10));
            quad[3]= sf::Vertex(sf::Vector2f(p.x + 10, p.y - 10));
            
            quad[0].texCoords = sf::Vector2f(0, 0);
            quad[1].texCoords = sf::Vector2f(20, 0);
            quad[2].texCoords = sf::Vector2f(20, 20);
            quad[3].texCoords = sf::Vector2f(0, 20);
            
            vertexArray.push_back(quad[0]);
            vertexArray.push_back(quad[1]);
            vertexArray.push_back(quad[2]);
            vertexArray.push_back(quad[3]);
        }
        
    }
    void generateEdgeArray()
    {
        edgeArray.clear();
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
            edgeArray.push_back(line[0]);
            edgeArray.push_back(line[1]);
        }
    }
    private:
        Layout<Graph>* layout;
        int sizex, sizey;
        std::vector<sf::Vertex> vertexArray;
        std::vector<sf::Vertex> edgeArray;
        
    };
}
#endif