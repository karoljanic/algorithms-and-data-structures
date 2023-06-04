#ifndef I_TREE_HPP
#define I_TREE_HPP

#include <cstddef>
#include <ostream>
#include <vector>

#include "TreeNode.hpp"

class Tree {
public:
    std::shared_ptr<TreeNode> root;
    size_t size;

    size_t comparisionNumber;
    size_t pointerManipulationsNumber;

    Tree();

    virtual void insertKey(unsigned int key) = 0;
    virtual void deleteKey(unsigned int key) = 0;

    std::shared_ptr<TreeNode> find(const std::shared_ptr<TreeNode>& root, unsigned int key);
    std::shared_ptr<TreeNode> successor(const std::shared_ptr<TreeNode>& root);
    
    size_t height(const std::shared_ptr<TreeNode>& root) const;
    size_t height() const;
    void printInOrder(std::ostream& os, const std::shared_ptr<TreeNode>& root);
    void print(std::ostream& os, const std::shared_ptr<TreeNode> root, ssize_t depth, char prefix, std::vector<char>& left_trace, std::vector<char>& right_trace) const;
    friend std::ostream& operator<<(std::ostream& os, const Tree& tree);

    virtual ~Tree();
};

#endif // I_TREE_HPP