#include "RBTree.hpp"

RBTree::RBTree() : Tree() { }

void RBTree::insertKey(unsigned int key) {
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

    std::shared_ptr<TreeNode> newNode{std::make_shared<TreeNode>(key, prev, TreeNode::Color::RED)};

    comparisionNumber++;
    pointerManipulationsNumber++;
    if(prev == nullptr) {
        root = newNode;
    }
    else if(key <= prev->key) {
        prev->left = newNode;
    }
    else {
        prev->right = newNode;
    }
    
    size++;

    fixInsert(newNode);
}

void RBTree::deleteKey(unsigned int key) {
    deleteNode(find(root, key));
}

void RBTree::deleteNode(std::shared_ptr<TreeNode> node) {
    if(node == nullptr)
        return;

    TreeNode::Color deletedColor = node->color;
    std::shared_ptr<TreeNode> x = node->parent;

    if(node->left == nullptr && node->right == nullptr) {
        pointerManipulationsNumber += 3;

        if(node->parent == nullptr)
            root = nullptr;
        else if(node->parent->left == node)
            node->parent->left = nullptr;
        else
            node->parent->right = nullptr;
    }
    else if(node->left == nullptr && node->right != nullptr) {
        pointerManipulationsNumber += 3;

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
        pointerManipulationsNumber += 3;

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

    if(deletedColor == TreeNode::Color::BLACK)
        fixDelete(x);

    size--;
}

void RBTree::fixInsert(std::shared_ptr<TreeNode> node) {
    if(node->parent == nullptr) {
        node->color = TreeNode::Color::BLACK;
        return;
    }

    while(node->parent->color == TreeNode::Color::RED) {
        pointerManipulationsNumber += 2
        ;
        if(node->parent->parent != nullptr && node->parent == node->parent->parent->right) {
            std::shared_ptr<TreeNode> uncle = node->parent->parent->left;
            if(uncle != nullptr && uncle->color == TreeNode::Color::RED) {
                uncle->color = TreeNode::Color::BLACK;
                node->parent->color = TreeNode::Color::BLACK;
                node->parent->parent->color = TreeNode::Color::RED;
                node = node->parent->parent;
            }
            else {
                if(node == node->parent->left) {
                    node = node->parent;
                    rightRotate(node);
                }
                node->parent->color = TreeNode::Color::BLACK;
                node->parent->parent->color = TreeNode::Color::RED;
                leftRotate(node->parent->parent);
            }
        }
        else {
            std::shared_ptr<TreeNode> uncle = node->parent->parent->right;
            if(uncle != nullptr && uncle->color == TreeNode::Color::RED) {
                uncle->color = TreeNode::Color::BLACK;
                node->parent->color = TreeNode::Color::BLACK;
                node->parent->parent->color = TreeNode::Color::RED;
                node = node->parent->parent;
            }
            else {
                if(node == node->parent->right) {
                    node = node->parent;
                    leftRotate(node);
                }
                node->parent->color = TreeNode::Color::BLACK;
                node->parent->parent->color = TreeNode::Color::RED;
                rightRotate(node->parent->parent);
            }
        }
        if(node == root)
            break;
    }
    root->color = TreeNode::Color::BLACK;
}

void RBTree::fixDelete(std::shared_ptr<TreeNode> node) {
    std::shared_ptr<TreeNode> w;

    while(node != root && node != nullptr && node->color == TreeNode::Color::BLACK) {
        pointerManipulationsNumber += 3;

        if(node->parent != nullptr && node == node->parent->left) {
            w = node->parent->right;

            if(w == nullptr)
                break;

            if(w->color == TreeNode::Color::RED) {
                w->color = TreeNode::Color::BLACK;
                node->parent->color = TreeNode::Color::RED;
                leftRotate(node->parent);
                w = node->parent->right;
            }

            if(w == nullptr)
                break;

            if(w != nullptr &&(w->left == nullptr || w->left->color == TreeNode::Color::BLACK) &&(w->right == nullptr || w->right->color == TreeNode::Color::BLACK)) {
                w->color = TreeNode::Color::RED;
                node = node->parent;
            }
            else if(w != nullptr) {
                if(w->right == nullptr || w->right->color == TreeNode::Color::BLACK) {
                    w->left->color = TreeNode::Color::BLACK;
                    w->color = TreeNode::Color::RED;
                    rightRotate(w);
                    w = node->parent->right;
                }
                w->color = node->parent->color;
                node->parent->color = TreeNode::Color::BLACK;
                w->right->color = TreeNode::Color::BLACK;
                leftRotate(node->parent);
                node = root;
            }
        }
        else {
            w = node->parent->left;

            if(w == nullptr)
                break;

            if(w->color == TreeNode::Color::RED) {
                w->color = TreeNode::Color::BLACK;
                node->parent->color = TreeNode::Color::RED;
                rightRotate(node->parent);
                w = node->parent->left;
            }

            if(w == nullptr)
                break;

            if(w != nullptr &&(w->left == nullptr || w->left->color == TreeNode::Color::BLACK) &&(w->right == nullptr || w->right->color == TreeNode::Color::BLACK)) {
                w->color = TreeNode::Color::BLACK;
                node = node->parent;
            }
            else if(w != nullptr) {
                if(w->left == nullptr || w->left->color == TreeNode::Color::BLACK) {
                    w->right->color = TreeNode::Color::BLACK;
                    w->color = TreeNode::Color::RED;
                    leftRotate(w);
                    w = node->parent->left;
                }
                w->color = node->parent->color;
                node->parent->color = TreeNode::Color::BLACK;
                w->left->color = TreeNode::Color::BLACK;
                leftRotate(node->parent);
                node = root;
            }
        }
    }

    if(node != nullptr)
        node->color = TreeNode::Color::BLACK;
}

void RBTree::leftRotate(std::shared_ptr<TreeNode> node) {
    pointerManipulationsNumber += 5;

    std::shared_ptr<TreeNode> y = node->right;
    node->right = y->left;
    if(y->left != nullptr) {
        y->left->parent = node;
    }

    y->parent = node->parent;
    if(node->parent == nullptr) {
        root = y;
    } 
    else if(node == node->parent->left) {
        node->parent->left = y;
    } 
    else {
        node->parent->right = y;
    }
    y->left = node;
    node->parent = y;
}

void RBTree::rightRotate(std::shared_ptr<TreeNode> node) {
    pointerManipulationsNumber += 5;
    
    std::shared_ptr<TreeNode> y = node->left;
    node->left = y->right;
    if(y->right != nullptr) {
        y->right->parent = node;
    }
    y->parent = node->parent;
    if(node->parent == nullptr) {
        root = y;
    } 
    else if(node == node->parent->right) {
        node->parent->right = y;
    } 
    else {
        node->parent->left = y;
    }
    y->right = node;
    node->parent = y;
}