#include "Runtime/GraphValue.hpp"
#include "Runtime/TypeOps.hpp"
#include "graph/algorithm/collections.hpp"
#include "Layout/BinaryTreeLayout.hpp"
#include "QtDisplay/WindowUI.hpp"
namespace spider
{
    std::pair<bool, int> left(GraphValue::Graph* g, int v)
    {
        auto children = graph::OutVertexList(*g, v);
        assert_size(children, lesser_eq(2), "Binary Tree Constraint");
        for (auto child : children)
            if (g->weight(v, child) == 1)
                return {true, child};
        return {false, -1};
    }
    std::pair<bool, int> right(GraphValue::Graph* g, int v)
    {
        auto children = graph::OutVertexList(*g, v);
        assert_size(children, lesser_eq(2), "Binary Tree Constraint");
        for (auto child : children)
            if (g->weight(v, child) == 2)
                return {true, child};
        return {false, -1};
    }
    Value* exp_tree_rot_right(std::vector<Value*> args)
    {
        assert_size(args, 2);
        assert_type(args[0], VType::Graph);
        assert_type(args[1], VType::Integer);
        GraphValue* g = getg(args[0]);
        int root = geti(args[1])->data;
        new WindowUI(g, new BinaryTreeLayout(*g, root));
        
        auto p = left(g->data, root);
        if (p.first == false)
            return g; // can not rotate right, no left child
        int leftchild = p.second;
        
        auto pleft = right(g->data, leftchild);
        g->data->removeEdge(root, leftchild);
        if (pleft.first)
        {
            g->data->removeEdge(leftchild, pleft.second);
            g->data->insertEdge(root, pleft.second, 1);
        }
        g->data->insertEdge(leftchild, root, 2);
        new WindowUI(g, new BinaryTreeLayout(*g, leftchild));
        
        return g;
    }
}