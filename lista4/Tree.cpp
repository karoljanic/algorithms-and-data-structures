#include "Tree.hpp"

Tree::Tree() :
    root{nullptr},
    size{0},
    comparisionNumber{0},
    pointerManipulationsNumber{0}
{ }

std::shared_ptr<TreeNode> Tree::find(const std::shared_ptr<TreeNode>& root, unsigned int key) {
    std::shared_ptr<TreeNode> tmp = root;

    while(tmp != nullptr) {
        comparisionNumber++;
        pointerManipulationsNumber++;

        if(key > tmp->key) {
            tmp = tmp->right;
        }
        else if(key < tmp->key) {
            tmp = tmp->left;
        }
        else {
            return tmp;
        }
    }

    return nullptr;
}

std::shared_ptr<TreeNode> Tree::successor(const std::shared_ptr<TreeNode>& root) {
    if(root->right != nullptr) {
        std::shared_ptr<TreeNode> tmp = root->right;
        while(tmp->left != nullptr) {
            tmp = tmp->left;
            pointerManipulationsNumber++;
        }

        return tmp;
    }
    
    std::shared_ptr<TreeNode> tmp = root;
    std::shared_ptr<TreeNode> prev = tmp->parent;
    while(prev != nullptr && tmp == prev->right) {
        pointerManipulationsNumber += 2;
        tmp = prev;
        prev = prev->parent;
    }

    return prev;
}

size_t Tree::height(const std::shared_ptr<TreeNode>& root) const {
    if(root == nullptr) {
        return 0;
    }

    size_t leftHeight = height(root->left);
    size_t rightHeight = height(root->right);

    return 1 + std::max(leftHeight, rightHeight);
}

size_t Tree::height() const {
    return height(root);
}

void Tree::printInOrder(std::ostream& os, const std::shared_ptr<TreeNode>& root) {
    if(root == nullptr)
        return;

    printInOrder(os, root->left);
    os << root->key << std::endl;
    printInOrder(os, root->right);
}

void Tree::print(std::ostream& os, const std::shared_ptr<TreeNode> root, ssize_t depth, char prefix, std::vector<char>& left_trace, std::vector<char>& right_trace) const {
    if (root == nullptr) {
        return;
    }
    
    if(root->left != nullptr) {
        print(os, root->left, depth + 1, '/', left_trace, right_trace);
    }

    if(prefix == '/') {
        left_trace[depth-1] = '|';
    }
    if(prefix == '\\') {
        right_trace[depth-1] = ' ';
    }
    if(depth == 0) {
        os << "-";
    }
    if(depth > 0) {
        os << " ";
    }
    
    for(ssize_t i = 0; i < depth - 1; i++) {
        if(left_trace[i] == '|' || right_trace[i] == '|') {
            os << "| ";
        }
        else {
            os << "  ";
        }
    }

    if(depth > 0) {
        os << prefix << "-";
    }

    os << "[" << root->key << "]" << std::endl;

    left_trace[depth] = ' ';

    if(root->right != nullptr) {
        right_trace[depth]='|';
        print(os, root->right, depth + 1, '\\', left_trace, right_trace);
    }
}

std::ostream& operator<<(std::ostream& os, const Tree& tree) {
    std::vector<char> leftTrace(tree.size, ' ');
    std::vector<char> rightTrace(tree.size, ' ');

    tree.print(os, tree.root, 0, '-', leftTrace, rightTrace);

    return os;
}

Tree::~Tree() { 

}