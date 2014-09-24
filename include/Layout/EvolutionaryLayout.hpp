#ifndef SPIDER_EVOLUTIONARY_LAYOUT_HPP
#define SPIDER_EVOLUTIONARY_LAYOUT_HPP
#include "Layout/ForceBasedLayout.hpp"
#include <vector>
#include <cstdlib>
#include <algorithm>
namespace spider
{
    template<typename Graph>
    class EvolutionaryLayout : public Layout<Graph>
    {
        typedef Layout<Graph> Base;
        typedef graph::VertexAttribute<Graph, Point> VA;
    public:
        EvolutionaryLayout(Graph& g):Base(g){};
        void generate(Rect bounds)
        {
            std::vector<VA> generation;
            for(int i = 0; i < 10; ++i)
            {
                ForceBasedLayout<Graph> l(Base::g);
                l.generate(bounds);
                generation.push_back(l.getVertexAttribute());
            }
            int iter = 1000; 
            while(iter--)
            {
                for (int i=0; i < 10; ++i)
                    for(int j=0; j < i/2; ++j)
                    {
                        if (i < 2 || j < 2 || rand()%100 > 95)
                        {
                            VA x = combine(generation[i], generation[j], bounds);
                            if (validate(x, bounds))
                                generation.push_back(x);
                        }
                    }
                    
                std::sort(generation.begin(), generation.end(), [&](VA x, VA y){return metric(x)>metric(y);});
                
                std::vector<VA> newgen(10);
                for (int i=0 ; i<10; ++i)
                    newgen[i] = generation[i];
                
                std::swap(generation,newgen);
            }
            Base::setVertexAttribute(generation[0]);
        }
    private:
        float metric(graph::VertexAttribute<Graph,Point>& layout)
        {
            float result = 0.0f;
            for(auto a = Base::g.begin(); a != Base::g.end(); ++a)
            {
                for (auto b = Base::g.begin(); b != Base::g.end(); ++b)
                {
                    if (a->first == b->first)
                        continue;
                    float d = Distance(layout.value(a->first),layout.value(b->first));
                    if ( ! graph::isAdjacent(Base::g, a->first, b->first))
                        result += d;
                    else 
                        result -= d;
                }
            }
            return result;
        }
        bool validate(VA& va, Rect bounds)
        {
            for (auto a = Base::g.begin(); a != Base::g.end(); ++a)
            {
                if (!Within(bounds, va.value(a->first)))
                    return false;
            }
            return true;
        }
        VA combine(VA& a, VA& b, Rect bounds)
        {
            VA result;
            for (auto x = Base::g.begin();  x!= Base::g.end(); ++x)
            {
                bool toss = rand()%100 > 50;
                result.value(x->first) = (toss ? a.value(x->first): b.value(x->first));
            }
            ForceBasedLayout<Graph> f(Base::g);
            f.generate(bounds, result);
            return f.getVertexAttribute();
        }
        
    };
}
#endif