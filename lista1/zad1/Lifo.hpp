// Lifo.hpp
// LIFO Implementation
// Karol Janic March 2023

#ifndef LIFO_HPP
#define LIFO_HPP

#include <iostream>

template<class T>
class LifoNode {
public:
    T data;
    LifoNode* next;

    LifoNode(T nodeData) : data(nodeData), next(nullptr) { }
};


template<class T>
class Lifo {
private:
    LifoNode<T>* topNode;

public:
    Lifo() : topNode(nullptr) { }

    void push(T data) {
        LifoNode<T>* tmp = new LifoNode(data);

        if(topNode == nullptr) {
            topNode = tmp;
        }
        else {
            tmp->next = topNode;
            topNode = tmp;
        }
    }

    void pop() {
        if(topNode == nullptr) {
            throw std::runtime_error("Stack is empty!");
        }

        LifoNode<T>* tmp = topNode;
        topNode = topNode->next;

        delete(tmp);
    }

    T top() const {
        if(topNode == nullptr) {
            throw std::runtime_error("Stack is empty!");
        }
        
        return topNode->data;
    }

    unsigned int size() const {
        unsigned int len = 0;

        LifoNode<T>* current = topNode;
        while(current != nullptr) {
            len++;
            current = current->next;
        }

        return len;
    }

    bool empty() const {
        return topNode == nullptr;
    }

    void clear() {
        LifoNode<T>* current = topNode;
        LifoNode<T>* tmp;

        while(current != nullptr) {
            tmp = current;
            current = current->next;

            delete(tmp);
        }

        topNode = nullptr;
    }

    void print(std::ostream& os) const {
        LifoNode<T>* current = topNode;

        while(current != nullptr) {
            os << current->data << " -> ";
            current = current->next;
        }
        os << "NULL";
    }

    friend std::ostream& operator<<(std::ostream& os, Lifo& lifo) {
        lifo.print(os);

        return os;
    }
    
    ~Lifo() {
        clear();
    }
};

#endif  // LIFO_HPP