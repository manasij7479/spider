#include <iostream>
#include <sstream>
#include "Layout/RandomLayout.hpp"
#include "Layout/ForceBasedLayout.hpp"
#include "Layout/CircularLayout.hpp"
#include "graph/util/generate.hpp"
#include "graph/algorithm/collections.hpp"
#include "Display/SceneDisplay.hpp"
#include "Display/GraphSprite.hpp"
#include "Display/TexRectangle.hpp"
#include "Display/SceneNode.hpp"
#include "External/OGDFAdapter.hpp"
#include "Event/EventManager.hpp"
#include "Runtime/UserGraph.hpp"
#include "Runtime/UserWindow.hpp"
#include "Runtime/Runtime.hpp"
int main()
{
    
    auto g = graph::gen::complete_bipartite(3,3);
    
    spider::EventManager eMgr;
    spider::UserGraph gWrap(&g);
    spider::UserWindow disp(&gWrap, &eMgr);
    gWrap.setCallback([&](){eMgr.reportRedrawEvent();});
    
    while(disp.isOpen())
    {
        std::string foo;
        std::getline(std::cin, foo);
        if (foo == ".q")
            eMgr.reportCloseEvent();
//         else if(foo == "toggleText")
//             gObj.toggleTextDisplay();
//         else if (foo == "rot")
//             gObj.handleRotate(1);
//         else if (foo[0] == 'c')
//         {
//             std::istringstream in(foo);
//             std::vector<std::string> args;
//             std::string temp;
//             while(in >> temp)
//                 args.push_back(temp);
//             args.erase(args.begin());
//             gWrap = spider::UserGraph(args);
//             gWrap.setCallback([&](){eMgr.reportRedrawEvent();});
//             gWrap.setNativeObj(gWrap.getNativeObj());
//         }
        else if(foo!="")
        {
            std::istringstream in(foo);
            std::vector<std::string> args;
            std::string temp;
            while(in >> temp)
                args.push_back(temp);
            gWrap.evalCommand(args);
        }
        
    }
}