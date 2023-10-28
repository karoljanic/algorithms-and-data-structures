#ifndef FIBONACCI_HEAP_HPP
#define FIBONACCI_HEAP_HPP

#include "heap.hpp"

template<typename T>
struct FNode {
    T data;
    size_t degree;
    bool marked;

    std::shared_ptr<FNode<T>> parent;
    std::shared_ptr<FNode<T>> child;
    std::shared_ptr<FNode<T>> prev;
    std::shared_ptr<FNode<T>> next;
};

template<typename T>
class FibonacciHeap : public Heap<T> {
private:
    std::shared_ptr<FNode<T>> minHead;
    size_t size;

    void initChild(std::shared_ptr<FNode<T>> parent, std::shared_ptr<FNode<T>> child) {
        child->prev = child->next=child;
        child->parent = parent;
        parent->degree++;
        parent->child = link(parent->child, child);
    }

    std::shared_ptr<FNode<T>> link(std::shared_ptr<FNode<T>>& node1, std::shared_ptr<FNode<T>>& node2) {
        if(node1 == nullptr) {
            return node2;
        }

        if(node2 == nullptr) {
            return node1;
        }

        this->keyComparisonsCounter++;
        if(node1->data > node2->data) {
            std::swap(node1, node2);
        }

        node1->next->prev = node2->prev;
        node2->prev->next = node1->next;

        node1->next = node2;
        node2->prev = node1;

        return node1;
    }

    std::shared_ptr<FNode<T>> extractMin(std::shared_ptr<FNode<T>> node) {
        if(node != nullptr && node->child != nullptr) {
            std::shared_ptr<FNode<T>> child = node->child;
            do {
                child->marked = false;
                child->parent = nullptr;
                child = child->next;
            } 
            while(child != node->child);
        }

        if(node->next == node) {
            node = node->child;
        } 
        else {
            node->next->prev = node->prev;
            node->prev->next = node->next;
            node = link(node->next, node->child);
        }
        
        if(node == nullptr) {
            return node;
        }  

        constexpr size_t maxChildDegree = 32;
        std::vector<std::shared_ptr<FNode<T>>> trees(maxChildDegree, nullptr);
        
        while(true) {
            if(trees[node->degree] != nullptr) {
                std::shared_ptr<FNode<T>> root = trees[node->degree];

                if(root == node) {
                    break;
                }

                trees[node->degree] = nullptr;
                
                this->keyComparisonsCounter++;
                if(node->data < root->data) {
                    root->prev->next = root->next;
                    root->next->prev = root->prev;
                    initChild(node, root);
                } 
                else {
                    root->prev->next = root->next;
                    root->next->prev = root->prev;

                    if(node->next == node) {
                        root->next = root->prev = root;
                    } 
                    else {
                        node->prev->next = root;
                        node->next->prev = root;
                        root->next = node->next;
                        root->prev = node->prev;
                    }
                    initChild(root, node);
                    node = root;
                }
                continue;
            } 
            else {
                trees[node->degree] = node;
            }

            node = node->next;
        }

        std::shared_ptr<FNode<T>> min = node;
        std::shared_ptr<FNode<T>> tmp = node;
        do {
            this->keyComparisonsCounter++;
            if(node->data < min->data) {
                min = node;
            }

            node = node->next;
        } 
        while(node != tmp);
        
        return min;
    }

public:
    FibonacciHeap() : Heap<T>(), minHead(nullptr), size{0} { }

    size_t getSize() const override { return size; }
    
    bool isEmpty() const override { return size == 0; }

    void insert(T data) override {
        std::shared_ptr<FNode<T>> newNode = std::make_shared<FNode<T>>((FNode<T>{data, 0, false, nullptr, nullptr, nullptr, nullptr}));
        newNode->prev = newNode;
        newNode->next = newNode;
        minHead = link(minHead, newNode);
        size++;
    }

    T getMin() override {
        if(minHead == nullptr) {
            throw std::runtime_error("Heap is empty!");
        }

        return minHead->data;
    }

    T extractMin() override {
        if(minHead == nullptr) {
            throw std::runtime_error("Heap is empty!");
        }

        std::shared_ptr<FNode<T>> oldMin = minHead;
        T oldMinKey = oldMin->data;

        minHead = extractMin(minHead);

        size--;

        return oldMinKey;
    }

    void merge(Heap<T>& otherHeap) override {
        FibonacciHeap<T>* castedOtherHeap = dynamic_cast<FibonacciHeap<T>*>(&otherHeap);
        if(castedOtherHeap == nullptr) {
            throw std::invalid_argument("Other heap must be instance of FibonacciHeap<T>!");
        }

        minHead = link(minHead, castedOtherHeap->minHead);
        size += castedOtherHeap->getSize();
    }
};

#endif // FIBONACCI_HEAP_HPP