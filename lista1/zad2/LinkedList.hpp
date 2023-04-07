// LinkedList.hpp
// Linked List Implementation
// Karol Janic March 2023

#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include <iostream>

template<class T>
class Node {
public:
    T data;
    Node<T>* next;

    Node(T nodeData) : data(nodeData), next(nullptr) { }
};


template<class T>
class LinkedList {
private:
    Node<T>* head;
    unsigned int length;

public:
    LinkedList() : head(nullptr), length(0) { }

    LinkedList(LinkedList& list1, LinkedList& list2) : head(list1.head), length(list1.length + list2.length) {
        if(list1.head == nullptr) {
            head = list2.head;
        }
        else if(list2.head != nullptr) {
            Node<T>* current = head;
            while(current->next != nullptr) {
                current = current->next;
            }
            current->next = list2.head;
        }

        list1.head = nullptr;
        list1.length = 0;

        list2.head = nullptr;
        list2.length = 0;
    } 

    void insertAtBeginning(T data) {
        Node<T>* tmp = new Node(data);

        if(head == nullptr) {
            head = tmp;
        }
        else {
            tmp->next = head;
            head = tmp;
        }

        length++;
    }

    void insertAtEnd(T data) {
        Node<T>* tmp = new Node(data);

        if(head == nullptr) {
            head = tmp;
        }
        else {
            Node<T>* current = head;
            while(current->next != nullptr) {
                current = current->next;
            }
            current->next = tmp;
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
            current->next = tmp;

            length++;
        }
    }

    T getFirstElement() const {
        return head->data;
    }

    T getLastElement() const {
        Node<T>* current = head;
        while(current->next != nullptr) {
            current = current->next;
        }
        
        return current->data;
    }

    T getElementAtPosition(int pos) const {
        Node<T>* current = head;
        while(pos > 0) {
            current = current->next;
            pos--;
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
            while(current != nullptr) {
                if(current->data == data) {
                    return pos;
                }

                current = current->next;
                pos++;
            }

            return -1;
        }    
    }

    void removeFromBeginning() {
        if(head == nullptr) {
            return;
        }

        Node<T>* tmp = head;
        head = head->next;

        delete(tmp);
        
        length--;
    }

    void removeFromEnd() {
        if(head == nullptr) {
            return;
        }

        Node<T>* current = head;
        Node<T>* beforeCurrent = nullptr;

        while(current->next != nullptr) {
            beforeCurrent = current;
            current = current->next;
        }

        if(beforeCurrent == nullptr) {
            delete(head);

            head = nullptr;
        }
        else {
            beforeCurrent->next = nullptr;
            delete(current);
        }

        length--;
    }

    void removeFromPosition(int pos) {
        if(pos >= length) {
            return;
        }
        
        if(pos == 0) {
            Node<T>* tmp = head;
            head = head->next;

            delete(tmp);
            length--;
        }
        else {
            Node<T>* current = head;
            for(int i = 0; i < pos-1; i++) {
                current = current->next;
            }

            Node<T>* tmp = current->next;
            current->next = current->next->next;

            delete(tmp);
            length--;
        }
    }

    void removeElement(T data) {
        if(head == nullptr) {
            return;
        }

        Node<T>* current = head;
        Node<T>* beforeCurrent = nullptr;

        while(current != nullptr) {
            if(current->data == data) {
                if(beforeCurrent == nullptr) {
                    head = current->next;
                    delete(current);
                }
                else {  
                    beforeCurrent->next = current->next;

                    delete(current);
                }   

                length--;

                return;
            }

            beforeCurrent = current;
            current = current->next;
        }
    }

    unsigned int size() const {
        return length;
    }

    bool empty() const {
        return head == nullptr;
    }

    void clear() {
        Node<T>* current = head;
        Node<T>* tmp;

        while(current != nullptr) {
            tmp = current;
            current = current->next;

            delete(tmp);
        }

        head = nullptr;
        length = 0;
    }

    void print(std::ostream& os) const {
        Node<T>* current = head;

        while(current != nullptr) {
            os << current->data << " -> ";
            current = current->next;
        }
        os << "NULL";
    }

    friend std::ostream& operator<<(std::ostream& os, LinkedList& linkedList) {
        linkedList.print(os);

        return os;
    }

    ~LinkedList() { 
        clear();
    }
};

#endif  // LINKED_LIST_HPP