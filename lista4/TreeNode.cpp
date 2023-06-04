#include "TreeNode.hpp"

TreeNode::TreeNode() : 
    key{std::numeric_limits<unsigned int>::lowest()},
    color{Color::BLACK},
    parent{nullptr},
    left{nullptr},
    right{nullptr}
{ }

TreeNode::TreeNode(unsigned int value, std::shared_ptr<TreeNode> parent) :
    key{value},
    color{Color::BLACK},
    parent{parent},
    left{nullptr},
    right{nullptr}
{ }

TreeNode::TreeNode(unsigned int value, std::shared_ptr<TreeNode> parent, Color color) :
    key{value},
    color{color},
    parent{parent},
    left{nullptr},
    right{nullptr}
{ }