#ifndef RBTREE_HPP
#define RBTREE_HPP

#include "Tree.hpp"

class RBTree : public Tree {
public:
    RBTree();

    void insertKey(unsigned int key) override;
    void deleteKey(unsigned int key) override;

    void deleteNode(std::shared_ptr<TreeNode> node);
    void fixInsert(std::shared_ptr<TreeNode> node);
    void fixDelete(std::shared_ptr<TreeNode> node);
    void leftRotate(std::shared_ptr<TreeNode> node);
    void rightRotate(std::shared_ptr<TreeNode> node);
};

#endif // RBTREE_HPP