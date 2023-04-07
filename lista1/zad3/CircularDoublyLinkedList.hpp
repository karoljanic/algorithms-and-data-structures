// CircularDoublyLinkedList.hpp
// Circular Doubly Linked List Implementation
// Karol Janic March 2023

#ifndef CIRCULAR_DOUBLY_LINKED_LIST_IMPLEMENTATION_HPP
#define CIRCULAR_DOUBLY_LINKED_LIST_IMPLEMENTATION_HPP

#include <iostream>

template<class T>
class Node {
public:
    T data;
    Node<T>* next;
    Node<T>* prev;

    Node(T nodeData) : data(nodeData), next(nullptr), prev(nullptr) { }
};


template<class T>
class CircularDoublyLinkedList {
private:
    Node<T>* head;
    unsigned int length;

public:
    CircularDoublyLinkedList() : head(nullptr), length(0) { }

    CircularDoublyLinkedList(CircularDoublyLinkedList& list1, CircularDoublyLinkedList& list2) : head(list1.head), length(list1.length + list2.length) {
        if(list1.head == nullptr) {
            head = list2.head;
        }
        else if(list2.head != nullptr) {
            Node<T>* tail1 = head->prev;
            Node<T>* tail2 = list2.head->prev;

            tail1->next = list2.head;
            list2.head->prev = tail1;
            tail2->next = head;
            head->prev = tail2;
        }

        list1.head = nullptr;
        list1.length = 0;

        list2.head = nullptr;
        list2.length = 0;
    }

    void insertAtBeginning(T data) {
        Node<T>* tmp = new Node(data);

        if(head == nullptr) {
            tmp->next = tmp;
            tmp->prev = tmp;
            head = tmp;
        }
        else {
            Node<T>* last = head->prev;

            tmp->next = head;
            tmp->prev = last;
            last->next = tmp;
            head->prev = tmp;
            head = tmp;
        }

        length++;
    }

    void insertAtEnd(T data) {
        Node<T>* tmp = new Node(data);

        if(head == nullptr) {
            tmp->next = tmp;
            tmp->prev = tmp;
            head = tmp;
        }
        else {
            Node<T>* last = head->prev;

            tmp->next = head;
            head->prev = tmp;
            tmp->prev = last;
            last->next = tmp;
        }

        length++;
    }

    void insertAtPosition(T data, unsigned int pos) {
        if(pos == 0) {
            insertAtBeginning(data);
        }
        else if(pos == length) {
            insertAtEnd(data);
        }
        else if(pos < length && pos > 0) {
            Node<T>* tmp = new Node(data);
            Node<T>* current = head;

            while(pos > 1) {
                current = current->next;
                pos--;
            }

            tmp->next = current->next;
            current->next->prev = tmp;
            current->next = tmp;
            tmp->prev = current;
            
        }
    }

    T getFirstElement() const {
        return head->data;
    }

    T getLastElement() const {
        return head->prev->data;
    }

    T getElementAtPosition(int pos) const {
        Node<T>* current = head;

        if(pos < (length >> 1)) {
            while(pos > 0) {
                current = current->next;
                pos--;
            }
        }
        else {
            while(pos != length) {
                current = current->prev;
                pos++;
            }
        }

        return current->data;
    }

    int find(T data) const {
        if(head == nullptr) {
            return -1;
        }
        else {
            int pos = 0;
            Node<T>* current = head;
            while(current->next != head) {
                if(current->data == data) {
                    return pos;
                }

                current = current->next;
                pos++;
            }

            if(current->data == data) {
                return pos;
            }

            return -1;
        }
    }

    void removeFromBeginning() {
        if(length == 1) {
            delete(head);
            head = nullptr;
            length = 0;
        }
        else if(length > 0) {
            Node<T>* tmp = head->prev;
            Node<T>* current = head;
            
            head = head->next;

            tmp->next = head;
            head->prev = tmp;

            delete(current);
            length--;
        }
    }

    void removeFromEnd() {
        if(length == 1) {
            delete(head);
            head = nullptr;
            length = 0;
        }
        else if(length > 0) {
            Node<T>* current = head->prev;
            Node<T>* prev = current->prev;

            prev->next = head;
            head->prev = prev;

            delete(current);
            length--;
        }
    }
    
    void removeFromPosition(int pos) {
        if(pos >= length) {
            return;
        }

        if(pos == 0) {
            removeFromBeginning();
        }
        else if(pos == (length - 1)) {
            removeFromEnd();
        }
        else {
            Node<T>* current = head;
            Node<T>* prev = nullptr;

            for(int i = 0; i < pos; i++) {
                prev = current;
                current = current->next;
            }

            prev->next = current->next;
            current->next->prev = prev;

            delete(current);
            length--;
        }
    }

    void removeElement(T data) {
        if(head == nullptr) {
            return;
        }

        Node<T>* current = head;
        Node<T>* prev = nullptr;

        while(current->data != data) {
            if(current->next == head) {
                return;
            }

            prev = current;
            current = current->next;
        }

        if(current->next == head && prev == nullptr) {
            delete(head);
            head = nullptr;
            
            length = 0;
            return;
        }

        if(current == head) {
            prev = head->prev;
            head = head->next;

            prev->next = head;
            head->prev = prev;

            delete(current);
            length--;
        }
        else if(current->next == head) {
            prev->next = head;
            head->prev = prev;

            delete(current);
            length--;
        }
        else {
            Node<T>* tmp = current->next;

            prev->next = tmp;
            tmp->prev = prev;

            delete(current);
            length--;
        }
    }

    unsigned int size() const {
        return length;
    }

    bool empty() const {
        return head == nullptr;
    }

    void reverse() {
        if(head == nullptr) {
            return;
        }

        Node<T>* prev = head;
        Node<T>* tmp = head;
        Node<T>* current = head->next;

        prev->next = prev;
        prev->prev = prev;

        while(current != head) {
            tmp = current->next;
            current->next = prev;
            prev->prev = current;
            head->next = current;
            current->prev = head;

            prev = current;
            current = tmp;
        }

        head = prev;
    }

    void clear() {
        if(head == nullptr) {
            return;
        }

        Node<T>* current = head;
        Node<T>* tmp;
        while(current->next != head) {
            tmp = current;
            current = current->next;

            delete(tmp);
        }

        delete(current);

        head = nullptr;
        length = 0;
    }

    ~CircularDoublyLinkedList() {
        clear();
    }

    void print(std::ostream& os) const {
        if(head == nullptr) {
            os << "NULL";
        }
        else {
            Node<T>* current = head;

            os << "<-> ";
            while(current->next != head) {
                os << current->data << " <-> ";
                current = current->next;
            }
            os << current->data << " <->";
        }
    }

    void printReversed(std::ostream& os) const {
        if(head == nullptr) {
            os << "NULL";
        }
        else {
            Node<T>* last = head->prev;
            Node<T>* current = last;

            os << "<-> ";
            while(current->prev != last) {
                os << current->data << " <-> ";
                current = current->prev;
            }
            os << current->data << " <->";
        }
    }

    friend std::ostream& operator<<(std::ostream& os, CircularDoublyLinkedList& circularDoublyLinkedList) {
        circularDoublyLinkedList.print(os);

        return os;
    }
    
};

#endif  // CIRCULAR_DOUBLY_LINKED_LIST_IMPLEMENTATION_HPP