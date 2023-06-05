#include <iostream>
#include <algorithm>
#include <random>
#include <fstream>

#include "BST.hpp"
#include "RBTree.hpp"
#include "SplayTree.hpp"

#undef EXTENSIVE_OUTPUT

std::random_device rd;
std::mt19937 gen(rd());

void randomVector(std::vector<unsigned int>& v, size_t size) {
    for(size_t  i = 0; i < size; i++) {
        v[i] = i;
    }

    std::shuffle(v.begin(), v.end(), gen);
}

void ascendingVector(std::vector<unsigned int>& v, size_t size) {
    for(size_t i = 0; i < size; i++) {
        v[i] = i;
    }
}

void  testDataStructure(Tree* tree, size_t n, std::vector<unsigned int> insertionsOrder, std::vector<unsigned int> deletionsOrder, std::ofstream& outputFile) {
    long long comparisionsNumberInsertSum = 0;
    long long comparisionsNumberInsertMax = 0;

    long long comparisionsNumberDeleteSum = 0;
    long long comparisionsNumberDeleteMax = 0;

    long long pointerManipulationsNumberInsertSum = 0;
    long long pointerManipulationsNumberInsertMax = 0;

    long long pointerManipulationsNumberDeleteSum = 0;
    long long pointerManipulationsNumberDeleteMax = 0;

    long long heightInsertSum = 0;
    long long heightInsertMax = 0;

    long long heightDeleteSum = 0;
    long long heightDeleteMax = 0;
    
    for(size_t i = 0; i < n; i++) {
        tree->comparisionNumber = 0;
        tree->pointerManipulationsNumber = 0;

        tree->insertKey(insertionsOrder[i]);

        size_t h = tree->height();
        comparisionsNumberInsertSum += tree->comparisionNumber;
        pointerManipulationsNumberInsertSum += tree->pointerManipulationsNumber;
        heightInsertSum += h;

        if(tree->comparisionNumber > comparisionsNumberInsertMax)
            comparisionsNumberInsertMax = tree->comparisionNumber;

        if(tree->pointerManipulationsNumber > pointerManipulationsNumberInsertMax)
            pointerManipulationsNumberInsertMax = tree->pointerManipulationsNumber;

        if(h > heightInsertMax)
            heightInsertMax = h;
    }

    for(size_t i = 0; i < n; i++) {
        tree->comparisionNumber = 0;
        tree->pointerManipulationsNumber = 0;

        tree->deleteKey(deletionsOrder[i]);

        size_t h = tree->height();
        comparisionsNumberDeleteSum += tree->comparisionNumber;
        pointerManipulationsNumberDeleteSum += tree->pointerManipulationsNumber;
        heightDeleteSum += h;

        if(tree->comparisionNumber > comparisionsNumberDeleteMax)
            comparisionsNumberDeleteMax = tree->comparisionNumber;

        if(tree->pointerManipulationsNumber > pointerManipulationsNumberDeleteMax)
            pointerManipulationsNumberDeleteMax = tree->pointerManipulationsNumber;

        if(h > heightDeleteMax)
            heightDeleteMax = h;
    }

    outputFile  << n << " "
                << static_cast<float>(comparisionsNumberInsertSum) / static_cast<float>(n) << " "
                << comparisionsNumberInsertMax << " "
                << static_cast<float>(comparisionsNumberDeleteSum) / static_cast<float>(n) << " "
                << comparisionsNumberDeleteMax << " "
                << static_cast<float>(pointerManipulationsNumberInsertSum) / static_cast<float>(n) << " "
                << pointerManipulationsNumberInsertMax << " "
                << static_cast<float>(pointerManipulationsNumberDeleteSum) / static_cast<float>(n) << " "
                << pointerManipulationsNumberDeleteMax << " "
                << static_cast<float>(heightInsertSum) / static_cast<float>(n) << " "
                << heightInsertMax << " "
                << static_cast<float>(heightDeleteSum) / static_cast<float>(n) << " "
                << heightDeleteMax << "\n";
}

int main(int argc, char* argv[]) {
    if(argc != 4)
        return -1;

    std::string dataStructure{argv[1]};
    std::string dataType{argv[2]};
    size_t n{static_cast<unsigned int>(std::atoi(argv[3]))};
    size_t range = 2 * n;

    std::vector<unsigned int> insertionsOrder(range, 0);
    if(dataType == "rand")
        randomVector(insertionsOrder, range);
    else if(dataType == "asc")
        ascendingVector(insertionsOrder, range);
    else 
        return -2;

    std::vector<unsigned int> deletionsOrder(range, 0);
    randomVector(deletionsOrder, range);

    Tree *tree;
    if(dataStructure == "bst")
        tree = new BST{};
    else if(dataStructure == "rbt")
        tree = new RBTree{};
    else if(dataStructure == "splay")
        tree = new SplayTree{};
    else
        return -2;


#ifdef EXTENSIVE_OUTPUT

    for(size_t i = 0; i < range; i++) {
        tree->insertKey(insertionsOrder[i]);
        std::cout << "insert " << insertionsOrder[i] << ":\n";
        std::cout << *(tree) << std::endl;
    }

    std::cout << "Height = " << tree->height() << std::endl;
    
    for(size_t i = 0; i < range; i++) {
        tree->deleteKey(deletionsOrder[i]);
        std::cout << "delete " << deletionsOrder[i] << ":\n";
        std::cout << *(tree) << std::endl;
    }

    std::cout << "Height = " << tree->height() << std::endl;

#else   
    std::string outputFileString = std::string(argv[1]) + "_" + std::string(argv[2]) + ".txt";
    std::ofstream outputFile{outputFileString};

    for(size_t i = 10000; i <= 100000; i+= 10000) {
        insertionsOrder.resize(i);

        std::cout << i;
        if(dataType == "rand")
            randomVector(insertionsOrder, i);
        else if(dataType == "asc")
            ascendingVector(insertionsOrder, i);

        deletionsOrder.resize(i);
        randomVector(deletionsOrder, i);
        if(tree->size != 0) {
            std::cout << "ERROR!\n";
            return -3;
        }

        testDataStructure(tree, i, insertionsOrder, deletionsOrder, outputFile);

        std::cout << " done!\n";
    }

#endif // EXTENSIVE_OUTPUT


    delete tree;

    return 0;
}