#include "Display/GraphSprite.hpp"
namespace spider
{
    void GraphSprite::generateVertexArray(Layout<Graph>* layout)
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
    void GraphSprite::generateEdgeArray(Layout<Graph>* layout)
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
    
    void GraphSprite::setLayout(Layout<Graph>* layout, int x, int y)
    {
        transform = sf::Transform::Identity;
//             trans = {0,0};
//             scale = {1.0f,1.0f};
        sizex = x;
        sizey = y;
        float border = 20;
        Rect bounds = {{0 + border,0 + border},{sizex * 1.0f - border , sizey * 1.0f - border}};
        layout->generate(bounds);
        generateEdgeArray(layout);
        generateVertexArray(layout);
        refreshVertexNames(&layout->getGraph());
    }
    void GraphSprite::draw(sf::RenderWindow* win, vec2 offset)
    {       
        sf::Transform finalt = transform;
        finalt.translate(offset.x, offset.y);
//         finalt.translate(offset.x, offset.y);
//         translate.translate(offset.x + trans.x ,offset.y + trans.y).scale(scale.x,scale.y, (float)sf::Mouse::getPosition(*win).x, (float)sf::Mouse::getPosition(*win).y);
//         translate.combine(transform);
        sf::RenderStates state(finalt);
        
        win->draw(edgeArray.data(),edgeArray.size(), sf::Lines, state);
        
        sf::Texture tex;
        tex.setSmooth(true);
        if (!tex.loadFromFile("resource/vertex.png")) 
            ; // do nothing..or maybe a log entry later
        else
            state.texture = &tex;
        
        win->draw(vertexArray.data(), vertexArray.size(), sf::Quads, state);
        
        if (displayNames)
        {
            sf::Font font;
            if(!font.loadFromFile("resource/courier.ttf"))
                throw std::runtime_error("Font loading failed");
            sf::Text t;
            t.setFont(font);
            t.setCharacterSize(20);
            t.setColor(sf::Color::Black);
            for (int i=1, j = 0; i< vertexArray.size(); i+=4, ++j)
            {
                t.setString(VertexNames[j]);
                t.setPosition(vertexArray[i].position.x,vertexArray[i].position.y);
                win->draw(t, state);
            }
        }

    }
    
    void GraphSprite::handleClick(float x,float y)
    {
//         std::cout <<"PRESSED: "<< x<<' '<< y<<std::endl; 
        if(x<=sizex && y<=sizey)
        {
            pressed=true;
            initial = {x,y};
        }
    }
    void GraphSprite::handleMoved(float x, float y)
    {
//         std::cout <<"MOVED: "<< x<<' '<< y<<std::endl;
        if (pressed == true && x<=sizex && x>=0 && y<=sizey && y>=0)
        {
//             trans = { trans.x + x - initial.x, trans.y + y - initial.y };
            transform.translate(x - initial.x, y-initial.y);
            initial = {x,y};
        }
    }
    void GraphSprite::handleReleased()
    {
//         std::cout<<"RELEASED\n";
        pressed = false;
    }
    
    void GraphSprite::handleEscape()
    {
//         std::cout<<"ESC\n";
        pressed = false;
//         trans  = {0,0};
        initial = {0,0};
//         scale = {1,1};
        transform = sf::Transform::Identity;
    }
    void GraphSprite::handleScroll(int ticks, float x, float y)
    {
//         std::cout<<"SCROLL:"<<ticks<<"\n";
        if(ticks>0)
//             scale = {scale.x * 1.2f, scale.y * 1.2f};
            transform.scale(1.2f, 1.2f, x, y);
        if(ticks<0)
//             scale = {scale.x * 0.8f, scale.y * 0.8f};
            transform.scale(0.8f, 0.8f, x, y);
        if(ticks != 0)
            ;
    }
    void GraphSprite::toggleTextDisplay()
    {
        displayNames = ! displayNames;
    }
    void GraphSprite::refreshVertexNames(Graph* g)
    {
        VertexNames = graph::VertexList(*g);
    }
    
}