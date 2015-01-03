#ifndef SPIDER_GRAPH_SPRITE
#define SPIDER_GRAPH_SPRITE
#include "Display/Sprite.hpp"
#include "graph/algorithm/collections.hpp"
#include <Layout/Geometry.hpp>
#include <Layout/Layout.hpp>
namespace spider
{
    class GraphSprite // Will be renamed after the above class is discarded
    : public Drawable
    {
        typedef graph::AdjacencyList<std::string, int> Graph;
    public:
        GraphSprite(Layout<Graph>* l, int x, int y) // x,y are no longer window sizes. local bounds are {(0,0),(x,y)}
        {
            pressed = false;
            displayNames = true;
            setLayout(l, x, y);
        }
        
        void setLayout(Layout<Graph>* layout, int x, int y);
        void draw(sf::RenderWindow* win, vec2 offset);
        
        void generateVertexArray(Layout<Graph>* layout);
        void generateEdgeArray(Layout<Graph>* layout);
        
        void handleClick(float x,float y);
        void handleMoved(float x, float y);
        void handleRotate(int dir);
        void handleReleased();
        
        void handleEscape();
        void handleScroll(int ticks, float x, float y);
        void toggleTextDisplay();

        void refreshVertexNames(Graph* g);
    private:
        int sizex, sizey;
        std::vector<sf::Vertex> vertexArray;
        std::vector<sf::Vertex> edgeArray;
        bool pressed;
        vec2 initial;
        sf::Transform transform;
        bool displayNames;
        std::vector<std::string> VertexNames;
        
        void fixInput(float& x, float& y)
        {
//             std::cout <<"ORI:"<<x<<' '<<y<<std::endl;
//             sf::Transform inv = transform.getInverse();
//             auto result = inv.transformPoint(x,y);
//             x = result.x;
//             y = result.y;
//             std::cout <<"NEW:"<<x<<' '<<y<<std::endl;
        }
        
    };
}
#endif