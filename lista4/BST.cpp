#include "BST.hpp"

BST::BST() 
    : Tree() { }

void BST::insertKey(unsigned int key) {
    std::shared_ptr<TreeNode> prev = nullptr;
    std::shared_ptr<TreeNode> tmp = root;

    while(tmp != nullptr) {
        prev = tmp;
        comparisionNumber++;
        pointerManipulationsNumber++;
        if(key < tmp->key) {
            tmp = tmp->left;
        }
        else {
            tmp = tmp->right;
        }
    }

    comparisionNumber++;
    pointerManipulationsNumber++;
    if(prev == nullptr) {
        root = std::make_shared<TreeNode>(key, prev);
    }
    else if(key <= prev->key) {
        prev->left = std::make_shared<TreeNode>(key, prev);
    }
    else {
        prev->right = std::make_shared<TreeNode>(key, prev);
    }
    
    size++;
}

void BST::deleteKey(unsigned int key) {
    deleteNode(find(root, key));
}

void BST::deleteNode(std::shared_ptr<TreeNode> node) {
    if(node == nullptr) {
        return;
    }

    pointerManipulationsNumber += 2;

    if(node->left == nullptr && node->right == nullptr) {
        if(node->parent == nullptr)
            root = nullptr;
        else if(node->parent->left == node)
            node->parent->left = nullptr;
        else
            node->parent->right = nullptr;
    }
    else if(node->left == nullptr && node->right != nullptr) {
        if(node->parent == nullptr) {
            root = node->right;
            root->parent = nullptr;
        }
        else if(node->parent->left == node) {
            node->right->parent = node->parent;
            node->parent->left = node->right;
        }
        else {
            node->right->parent = node->parent;
            node->parent->right = node->right;
        }
    }
    else if(node->left != nullptr && node->right == nullptr) {
        if(node->parent == nullptr) {
            root = node->left;
            root->parent = nullptr;
        }
        else if(node->parent->left == node) {
            node->left->parent = node->parent;
            node->parent->left = node->left;
        }
        else {
            node->left->parent = node->parent;  
            node->parent->right = node->left;
        }
    }
    else {
        std::shared_ptr<TreeNode> succ = successor(node);
        node->key = succ->key;
        deleteNode(succ);

        return;
    }

    size--;
}