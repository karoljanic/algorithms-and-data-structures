#ifndef BINOMIAL_HEAP_HPP
#define BINOMIAL_HEAP_HPP

#include <memory>
#include <stack>
#include <stdexcept>

#include "heap.hpp"

template<typename T>
struct BNode {
    T data;
    unsigned int degree;
    std::shared_ptr<BNode<T>> child, sibling, parent;
};


template<typename T>
class BinomialHeap : public Heap<T> {
private:
    std::shared_ptr<BNode<T>> head;
    size_t size;

    BinomialHeap(std::shared_ptr<BNode<T>> head): Heap<T>{}, head{head}, size{0} { }

    void link(std::shared_ptr<BNode<T>>& node1, std::shared_ptr<BNode<T>>& node2) {
        node2->parent = node1;
        node2->sibling = node1->child;
        node1->child = node2;
        node1->degree++;
    }

public:
    BinomialHeap(): head(nullptr), size{0} { }

    size_t getSize() const override { return size; }
    
    bool isEmpty() const override { return size == 0; }

    void insert(T data) override {
		BinomialHeap heap{std::make_shared<BNode<T>>((BNode<T>{data, 0, nullptr, nullptr, nullptr}))};
		merge(heap);
        size++;
	}

    T getMin() override {
        if(head == nullptr) {
            throw std::runtime_error("Heap is empty!");
        }

        std::shared_ptr<BNode<T>> curr = head;
        T minKey = head->data;

        while(curr != nullptr) {
            this->keyComparisonsCounter++;
            if(curr->data < minKey) {
                minKey = curr->data;
            }

            curr = curr->sibling;
        }

        return minKey;
    }

    T extractMin() override {
        if(head == nullptr) {
            throw std::runtime_error("Heap is empty!");
        }

        std::shared_ptr<BNode<T>> curr = head;
        std::shared_ptr<BNode<T>> prev = nullptr;

        T minKey = head->data;
        std::shared_ptr<BNode<T>> minBNode = nullptr;
        std::shared_ptr<BNode<T>> minBNodePrev = nullptr;

        while(curr != nullptr) {
            this->keyComparisonsCounter++;
            if(curr->data <= minKey) {
                minKey = curr->data;
                minBNode = curr;
                minBNodePrev = prev;
            }

            prev = curr;
            curr = curr->sibling;
        }

        if(minBNodePrev != nullptr) {
            minBNodePrev->sibling = minBNode->sibling;
        }
        else {
            head = minBNode->sibling;
        }

        if(minBNode->child != nullptr) {
            std::stack<std::shared_ptr<BNode<T>>> s;
            std::shared_ptr<BNode<T>> child = minBNode->child;
            while(child != nullptr) {
                s.push(child);

                child->parent = nullptr;
                child = child->sibling;
            }

            std::shared_ptr<BNode<T>> reversedHead = s.top();
            s.pop();
            curr = reversedHead;

            while(!s.empty()) {
                curr->sibling = s.top();
                s.pop();
                curr = curr->sibling;
            }
            curr->sibling = nullptr;

            BinomialHeap<T> reversedHeap(reversedHead);
            merge(reversedHeap);
        }

        size--;

        return minKey;
    }

    void merge(Heap<T>& otherHeap) override {
        BinomialHeap<T>* castedOtherHeap = dynamic_cast<BinomialHeap<T>*>(&otherHeap);
        if(castedOtherHeap == nullptr) {
            throw std::invalid_argument("Other heap must be instance of BinomialHeap<T>!");
        }

        if(head == nullptr) {
            head = castedOtherHeap->head;
            return;
        }

        std::shared_ptr<BNode<T>> curr1 = head;
        std::shared_ptr<BNode<T>> curr2 = castedOtherHeap->head;
        std::shared_ptr<BNode<T>> curr3 = nullptr;
        std::shared_ptr<BNode<T>> tmp = nullptr;

        if(curr1->degree <= curr2->degree) {
            curr3 = curr1;
            curr1 = curr1->sibling;
        }
        else {
            curr3 = curr2;
            curr2 = curr2->sibling;
        }
        tmp = curr3;

        while(curr1 != nullptr && curr2 != nullptr) {
            if(curr1->degree <= curr2->degree) {
                curr3->sibling = curr1;
                curr1 = curr1->sibling;
            }
            else {
                curr3->sibling = curr2;
                curr2 = curr2->sibling;
            }
            curr3 = curr3->sibling;
        }

        while(curr1 != nullptr) {
            curr3->sibling = curr1;
            curr1 = curr1->sibling;
            curr3 = curr3->sibling;
        }
        while(curr2 != nullptr) {
            curr3->sibling = curr2;
            curr2 = curr2->sibling;
            curr3 = curr3->sibling;
        }

        curr3 = tmp;
        std::shared_ptr<BNode<T>> prev = nullptr;
        std::shared_ptr<BNode<T>> next = curr3->sibling;

        while(next != nullptr) {
            if((curr3->degree != next->degree) || (next->sibling != nullptr && curr3->degree == next->sibling->degree)) {
                prev = curr3;
                curr3 = next;
            }
            else {
                this->keyComparisonsCounter++;
                if(curr3->data <= next->data) {
                    curr3->sibling = next->sibling;
                    link(curr3, next);
                }
                else {
                    if(prev == nullptr)
                        tmp = next;
                    else
                        prev->sibling = next;

                    link(next, curr3);
                    curr3 = next;
                }
            }

            next = curr3->sibling;
        }

        head = tmp;
        size += otherHeap.getSize();
    }
};

#endif // BINOMIAL_HEAP_HPP