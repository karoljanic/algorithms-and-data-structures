#include "SplayTree.hpp"

SplayTree::SplayTree() : Tree() { }

void SplayTree::insertKey(unsigned int key) {
    this->root = this->splayInsert(key);
    
    this->size++;
}

void SplayTree::deleteKey(unsigned int key) {
    root = deleteTreeNode(key);
}

std::shared_ptr<TreeNode> SplayTree::splay(std::shared_ptr<TreeNode> root, unsigned int key) {
    if(root == nullptr || root->key == key)
        return root;
    
    comparisionNumber++;
    if(root->key > key) {
        if(root->left == nullptr)
            return root;

        comparisionNumber++;
        if(root->left->key > key) {
            pointerManipulationsNumber += 2;
            root->left->left = splay(root->left->left, key);
            root = rightRotate(root);
        }
        else if(root->left->key < key) {
            pointerManipulationsNumber++;
            root->left->right = splay(root->left->right, key);
 
            if(root->left->right != nullptr) {
                pointerManipulationsNumber++;
                root->left = leftRotate(root->left);
            }
        }
 
        return(root->left == nullptr) ? root : rightRotate(root);
    }
    else {
        if(root->right == nullptr)
            return root;
    
        comparisionNumber++;
        if(root->right->key > key) {
            pointerManipulationsNumber++;
            root->right->left = splay(root->right->left, key);
 
            if(root->right->left != nullptr) {
                pointerManipulationsNumber++;
                root->right = rightRotate(root->right);
            }
        }
        else if(root->right->key < key) {
            pointerManipulationsNumber += 2;
            root->right->right = splay(root->right->right, key);
            root = leftRotate(root);
        }
 
        return(root->right == nullptr) ? root : leftRotate(root);
    }
}

std::shared_ptr<TreeNode> SplayTree::splayInsert(unsigned int key) {
    if(root == nullptr) {
        std::shared_ptr<TreeNode> newNode = std::make_shared<TreeNode>();
        pointerManipulationsNumber++;
        newNode->key = key;
        return newNode;
    }
    
    pointerManipulationsNumber += 3;
    root = splay(root, key);
    
    comparisionNumber++;
    if(root->key == key)
        return root;
 
    std::shared_ptr<TreeNode> newnode = std::make_shared<TreeNode>();
    newnode->key = key;
    
    comparisionNumber++;
    if(root->key > key) {
        pointerManipulationsNumber += 3;
        newnode->right = root;
        newnode->left = root->left;
        root->left = nullptr;
    }
    else {
        pointerManipulationsNumber += 3;
        newnode->left = root;
        newnode->right = root->right;
        root->right = nullptr;
    }
 
    return newnode;
}

std::shared_ptr<TreeNode> SplayTree::deleteTreeNode(unsigned int key) {
    std::shared_ptr<TreeNode> temp;
    if(root == nullptr)
        return nullptr;
  
    pointerManipulationsNumber++;
    root = splay(root, key);
    
    comparisionNumber++;
    if(key != root->key)
        return root;
    
    if(root->left == nullptr) {
        pointerManipulationsNumber += 2;
        temp = root;
        root = root->right;
    }
    else {
        pointerManipulationsNumber += 3;
        temp = root;
        root = splay(root->left, key);
        root->right = temp->right;
    }
  
    this->size--;

    return root;
}

std::shared_ptr<TreeNode> SplayTree::rightRotate(std::shared_ptr<TreeNode> node) {
    pointerManipulationsNumber += 3;

    std::shared_ptr<TreeNode> y = node->left;
    node->left = y->right;
    y->right = node;
    return y;
}   

std::shared_ptr<TreeNode> SplayTree::leftRotate(std::shared_ptr<TreeNode> node) {
    pointerManipulationsNumber += 3;

    std::shared_ptr<TreeNode> y = node->right;
    node->right = y->left;
    y->left = node;
    return y;
}