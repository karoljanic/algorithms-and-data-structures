#ifndef SPLAY_TREE_HPP
#define SPLAY_TREE_HPP

#include "Tree.hpp"

class SplayTree : public Tree {
public:
    SplayTree();

    void insertKey(unsigned int key) override;
    void deleteKey(unsigned int key) override;

    std::shared_ptr<TreeNode> splay(std::shared_ptr<TreeNode> root, unsigned int key);
    std::shared_ptr<TreeNode> splayInsert(unsigned int key);
    std::shared_ptr<TreeNode> deleteTreeNode(unsigned int key);
    std::shared_ptr<TreeNode> rightRotate(std::shared_ptr<TreeNode> node);
    std::shared_ptr<TreeNode> leftRotate(std::shared_ptr<TreeNode> node);
};

#endif // SPLAY_TREE_HPP