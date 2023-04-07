// Fifo.hpp
// FIFO Implementation
// Karol Janic March 2023

#ifndef FIFO_HPP
#define FIFO_HPP

#include <iostream>

template<class T>
class FifoNode {
public:
    T data;
    FifoNode* next;

    FifoNode(T nodeData) : data(nodeData), next(nullptr) { }
};


template<class T>
class Fifo {
private:
    FifoNode<T>* frontNode;
    FifoNode<T>* backNode;

public:
    Fifo() : frontNode(nullptr), backNode(nullptr) { }

    void push(T data) {
        FifoNode<T>* tmp = new FifoNode(data);

        if(backNode == nullptr) {
            frontNode = tmp;
            backNode = tmp;
        }
        else {
            backNode->next = tmp;
            backNode = tmp;
        }
    }

    void pop() {
        if(frontNode == nullptr) {
            throw std::runtime_error("Queue is empty!");
        }
        
        FifoNode<T>* tmp = frontNode;
        frontNode = frontNode->next;

        if(frontNode == nullptr) {
            backNode = nullptr;
        }

        delete(tmp);
    }

    T front() const {
        if(frontNode == nullptr) {
            throw std::runtime_error("Queue is empty!");
        }
        
        return frontNode->data;
    }

    T back() const {
        if(backNode == nullptr) {
            throw std::runtime_error("Queue is empty!");
        }
        
        return backNode->data;
    }

    unsigned int size() const {
        unsigned int len = 0;

        FifoNode<T>* current = frontNode;
        while(current != nullptr) {
            len++;
            current = current->next;
        }

        return len;
    }

    bool empty() const {
        return frontNode == nullptr;
    }

    void clear() {
        FifoNode<T>* current = frontNode;
        FifoNode<T>* tmp;

        while(current != nullptr) {
            tmp = current;
            current = current->next;

            delete(tmp);
        }

        frontNode = nullptr;
        backNode = nullptr;
    }

    void print(std::ostream& os) const {
        FifoNode<T>* current = frontNode;

        while(current != nullptr) {
            os << current->data << " -> ";
            current = current->next;
        }
        os << "NULL";
    }

    friend std::ostream& operator<<(std::ostream& os, Fifo& fifo) {
        fifo.print(os);

        return os;
    }

    ~Fifo() {
        clear();
    }
};

#endif  // FIFO_HPP