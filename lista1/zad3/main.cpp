#include "CircularDoublyLinkedList.hpp"
#include "../RandomNumberGenerator.hpp"
#include "../Clock.hpp"

#include <iostream>

void testMerge() {
    constexpr int list1Size = 3;
    constexpr int list2Size = 4;

    CircularDoublyLinkedList<int> list1;
    for(int i = 0; i < list1Size; i++) {
        list1.insertAtBeginning(i);
    }

    CircularDoublyLinkedList<int> list2;
    for(int i = list1Size; i < list1Size + list2Size; i++) {
        list2.insertAtBeginning(i);
    }

    std::cout << std::endl;
    std::cout << "List 1 before merge: " << list1 << "\nList 2 before merge: " << list2 << std::endl;

    CircularDoublyLinkedList<int> mergedLists(list1, list2);

    std::cout << "Merged lists:        " << mergedLists << std::endl;
    std::cout << "List 1 after merge:  " << list1 << "\nList 2 after merge:  " << list2 << std::endl;
}

double meanTimeToAccessElement(const CircularDoublyLinkedList<int>& list, int elementIndex) {
    constexpr int triesNumber = 1000;

    Clock clock = Clock();
    clock.startMeasurement();

    for(int i = 0; i < triesNumber; i++) {
        int item = list.getElementAtPosition(elementIndex);
    }

    return clock.takeMeasurement(false) / triesNumber;
}

double meanTimeToAccessRandomElement(const CircularDoublyLinkedList<int>& list, int minElementIndex, int maxElementIndex) {
    constexpr int triesNumber = 1000;

    Clock clock = Clock();
    clock.startMeasurement();

    RandomNumberGenerator rng = RandomNumberGenerator();

    for(int i = 0; i < triesNumber; i++) {
        int item = list.getElementAtPosition(rng.get(minElementIndex, maxElementIndex));
    }

    return clock.takeMeasurement(false) / triesNumber;
}

int main(int argc, char** argv) {
    if(argc != 2) {
        return 0;
    }

    int samplesNumber = std::stoi(argv[1]);

    constexpr int randomNumberLowerBound = 0;
    constexpr int randomNumberUpperBound = 1000;

    RandomNumberGenerator rng = RandomNumberGenerator();

    CircularDoublyLinkedList<int> list;
    for(int i = 0; i < samplesNumber; i++) {
        list.insertAtEnd(rng.get(randomNumberLowerBound, randomNumberUpperBound));
    }

    std::cout << meanTimeToAccessElement(list, 0) << std::endl;
    std::cout << meanTimeToAccessElement(list, samplesNumber / 2) << std::endl;
    std::cout << meanTimeToAccessElement(list, samplesNumber - 1) << std::endl;
    std::cout << meanTimeToAccessRandomElement(list, 0, samplesNumber - 1) << std::endl;

    testMerge();

    return 0;
}