#include <iostream>
#include <iomanip>
#include <vector>

#define EXTENSIVE_OUTPUT

unsigned long comparisonsCounter = 0;
unsigned long swapsCounter = 0;


bool cmp(int a, int b) {
    comparisonsCounter++;

    return a > b;
}

void swap(int& a, int& b) {
    swapsCounter++;

    int tmp = a;
    a = b;
    b = tmp;
}

void insertionSort(std::vector<int>& array) {
    for(size_t i = 1; i < array.size(); i++) {
        int key = array[i];
        size_t j = i;

        while(j > 0 && cmp(array[j - 1], key)) {
            swap(array[j],  array[j - 1]);
            j--;
        }

#ifdef EXTENSIVE_OUTPUT

    for(const int& element : array) {
        std::cout << std::setw(2) << element << ' ';
    }
    std::cout << '\n';

#endif  // EXTENSIVE_OUTPUT

    }
}

bool isSorted(std::vector<int>& array) {
    for(size_t i = 1; i < array.size(); i++) {
        if(array[i - 1] > array[i]) {
            return false;
        } 
    }

    return true;
}


int main(int argc, char** argv) {
    size_t n;
    std::cin >> n;
    
    std::vector<int> array;
    array.reserve(n);
    int tmp;
    while(n > 0) {
        std::cin >> tmp;
        array.push_back(tmp);
        n--;
    }

    comparisonsCounter = 0;
    swapsCounter = 0;

    insertionSort(array);

    
#ifdef EXTENSIVE_OUTPUT

    for(const int& element : array) {
        std::cout << std::setw(2) << element << ' ';
    }
    std::cout << '\n';

    std::cout << "is sorted: " << isSorted(array) << '\n' <<
        "cmps: " << comparisonsCounter << '\n' <<
        "swps: " << swapsCounter << '\n';

#else

    std::cout << isSorted(array) << '\n' << comparisonsCounter << '\n' << swapsCounter << '\n';

#endif  // EXTENSIVE_OUTPUT

}