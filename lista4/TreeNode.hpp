#ifndef TREE_NODE_HPP
#define TREE_NODE_HPP

#include <memory>
#include <limits>

class TreeNode {
public:
    enum class Color { NONE, RED, BLACK };

    unsigned int key;
    Color color;

    std::shared_ptr<TreeNode> parent;
    std::shared_ptr<TreeNode> left;
    std::shared_ptr<TreeNode> right;

    TreeNode();
    TreeNode(unsigned int value, std::shared_ptr<TreeNode> parent);
    TreeNode(unsigned int value, std::shared_ptr<TreeNode> parent, Color color);
};

#endif // TREE_NODE_HPP