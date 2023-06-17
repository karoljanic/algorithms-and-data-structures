#ifndef HEAP_HPP
#define HEAP_HPP

template<typename T>
class Heap {
protected:
    size_t keyComparisonsCounter;

public:
    Heap() : keyComparisonsCounter{0} { }

    void clearKeyComparisonsCounter() { keyComparisonsCounter = 0; }
    size_t getKeyComparisonsCounter() const { return keyComparisonsCounter; }

    virtual size_t getSize() const = 0;
    virtual bool isEmpty() const = 0;
    virtual void insert(T data) = 0;
    virtual T getMin() = 0;
    virtual T extractMin() = 0;
    virtual void merge(Heap<T>& otherHeap) = 0;

    virtual ~Heap() { }
};

#endif // HEAP_HPP
