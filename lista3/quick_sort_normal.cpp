#include <iostream>
#include <iomanip>
#include <vector>
#include <chrono>

#undef EXTENSIVE_OUTPUT

unsigned long comparisonsCounter = 0;
unsigned long swapsCounter = 0;


bool smaller(int a, int b) {
    comparisonsCounter++;

    return a < b;
}


bool greater(int a, int b) {
    comparisonsCounter++;

    return a > b;
}


void swap(int& a, int& b) {
    swapsCounter++;

    int tmp = a;
    a = b;
    b = tmp;
}


size_t quickSortPartition(std::vector<int>& array, size_t left, size_t right) {
    size_t i = left - 1;
    size_t j = right + 1;
    int pivot = array[(left + right) / 2];

    while(true) {
        do {
            i++;
        } while(smaller(array[i], pivot));

        do {
            j--;
        } while(greater(array[j], pivot));

        if( i >= j) {
            return j;
        }

        swap(array[i], array[j]);
    }
}


void quickSort(std::vector<int>& array, size_t left, size_t right) {
    if(right <= left) {
        return;
    }

    size_t p = quickSortPartition(array, left, right);

#ifdef EXTENSIVE_OUTPUT

    for(const int& element : array) {
        std::cout << std::setw(2) << element << ' ';
    }
    std::cout << '\n';

#endif  // EXTENSIVE_OUTPUT

    quickSort(array, left, p);
    quickSort(array, p + 1, right);
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
    size_t m = n;
    while(m > 0) {
        std::cin >> tmp;
        array.push_back(tmp);
        m--;
    }

    comparisonsCounter = 0;
    swapsCounter = 0;

    auto start = std::chrono::steady_clock::now();
    quickSort(array, 0, n-1);
    auto end = std::chrono::steady_clock::now();

    std::chrono::duration<double> elapsed_seconds = end-start;

#ifdef EXTENSIVE_OUTPUT

    for(const int& element : array) {
        std::cout << std::setw(2) << element << ' ';
    }
    std::cout << '\n';

    std::cout << "is sorted: " << isSorted(array) << '\n' <<
        "cmps: " << comparisonsCounter << '\n' <<
        "swps: " << swapsCounter << '\n' <<
        "time: " << elapsed_seconds.count() * 1000 << '\n';

#else

    std::cout << isSorted(array) << '\n' << comparisonsCounter << '\n' << swapsCounter << '\n' << elapsed_seconds.count() * 1000 << '\n';
    
#endif  // EXTENSIVE_OUTPUT
        
}