#include <iostream>
#include <fstream>
#include <random>
#include <time.h>
#include <vector>

#include "binomial_heap.hpp"
#include "fibonacci_heap.hpp"

static unsigned int comaprisonCount = 0;

int main(int argc, char* argv[]) {
    if(argc == 5) {
        std::string heapType{argv[1]};
        size_t n{static_cast<size_t>(atoi(argv[2]))};
        size_t k{static_cast<size_t>(atoi(argv[3]))};
        std::string outputFilePrefix{argv[4]};

        std::mt19937 rgn{std::random_device{}()};
        std::uniform_int_distribution<int> dis(0, 5 * n);

        for(size_t i = 0; i < k; i++) {
            std::ofstream file{outputFilePrefix + "-" + std::to_string(i) + ".txt"};

            Heap<int>* heap1;
            Heap<int>* heap2;
            if(heapType == "bin") {
                heap1 = new BinomialHeap<int>();
                heap2 = new BinomialHeap<int>();
            }
            else if(heapType == "fib") {
                heap1 = new FibonacciHeap<int>();
                heap2 = new FibonacciHeap<int>();
            }
            else {
                return 0;
            }

            size_t instructionCounter = 0;
            size_t lastKeyComparisonsCounter = 0;
            for(size_t i = 0; i < n; i++) {
                heap1->insert(dis(rgn));
                
                file << instructionCounter << " " << (heap1->getKeyComparisonsCounter() - lastKeyComparisonsCounter) << std::endl;
                lastKeyComparisonsCounter = heap1->getKeyComparisonsCounter();
                instructionCounter++;
            }

            lastKeyComparisonsCounter = 0;
            for(size_t i = 0; i < n; i++) {
                heap2->insert(dis(rgn));

                file << instructionCounter << " " << (heap2->getKeyComparisonsCounter() - lastKeyComparisonsCounter) << std::endl;
                lastKeyComparisonsCounter = heap2->getKeyComparisonsCounter();
                instructionCounter++;
            }        

            heap1->merge(*heap2);

            std::vector<int> extractedKeysOrder{};
            extractedKeysOrder.reserve(2 * n);
            for(size_t i = 0; i < 2 * n; i++) {
                extractedKeysOrder.emplace_back(heap1->extractMin());

                file << instructionCounter << " " << (heap1->getKeyComparisonsCounter() - lastKeyComparisonsCounter) << std::endl;
                lastKeyComparisonsCounter = heap1->getKeyComparisonsCounter();
                instructionCounter++;
            }

            if(!heap1->isEmpty()) {
                std::cout << "Merged Heap After 2n extractions is not empty!. Left " << heap1->getSize() << std::endl;
            }

            for(size_t i = 0; i < 2 * n - 1; i++) {
                if(extractedKeysOrder[i] > extractedKeysOrder[i + 1]) {
                    std::cout << "Incorrect Keys Order!\n";
                }
            }
        }
    }
    else if(argc == 7) {
        std::string heapType{argv[1]};
        size_t nMin{static_cast<size_t>(atoi(argv[2]))};
        size_t nMax{static_cast<size_t>(atoi(argv[3]))};
        size_t step{static_cast<size_t>(atoi(argv[4]))};
        size_t repeats{static_cast<size_t>(atoi(argv[5]))};
        std::string outputFile{argv[6]};

        std::mt19937 rgn{std::random_device{}()};
        std::uniform_int_distribution<int> dis(0, 5 * nMax);

        std::ofstream file{outputFile};

        for(size_t n = nMin; n < nMax; n += step) {
            size_t sum = 0;
            for(size_t k = 0; k < repeats; k++) {
                Heap<int>* heap1;
                Heap<int>* heap2;
                if(heapType == "bin") {
                    heap1 = new BinomialHeap<int>();
                    heap2 = new BinomialHeap<int>();
                }
                else if(heapType == "fib") {
                    heap1 = new FibonacciHeap<int>();
                    heap2 = new FibonacciHeap<int>();
                }
                else {
                    return 0;
                }

                for(size_t i = 0; i < n; i++) {
                    heap1->insert(dis(rgn));
                    heap2->insert(dis(rgn));
                }

                heap1->merge(*heap2);

                for(size_t i = 0; i < 2 * n; i++) {
                    heap1->extractMin();
                }

                sum += heap1->getKeyComparisonsCounter();
                sum += heap2->getKeyComparisonsCounter();
            }

            file << std::to_string(n) << " " << static_cast<float>(sum) / static_cast<float>(repeats) << std::endl; 
        }
    }

    return 0;
}