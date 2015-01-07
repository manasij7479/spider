// #include <ogdf/basic/Graph_d.h>
// #include "../graph/graph.hpp"
// #include "../graph/algorithm/collections.hpp"
// namespace spider
// {
//     ogdf::Graph ConvertToOGDF(graph::Graph<int,bool>& g)
//     {
//         ogdf::Graph result;
//         std::map<int, ogdf::node> nodemap;
//         for (auto v : graph::VertexList(g))
//             nodemap[v] = result.newNode(v);
//         for (auto e : graph::EdgeList(g))
//             result.newEdge(nodemap[std::get<0>(e)],nodemap[std::get<1>(e)]);
//         return result;
//     }
// 
// }