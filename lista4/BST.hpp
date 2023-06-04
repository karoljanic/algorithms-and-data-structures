#ifndef BST_HPP
#define BST_HPP

#include "Tree.hpp"

class BST : public Tree {
public:
    BST();
    
    void insertKey(unsigned int key) override;
    void deleteKey(unsigned int key) override;

    void deleteNode(std::shared_ptr<TreeNode> node);
};

#endif // BST_HPP