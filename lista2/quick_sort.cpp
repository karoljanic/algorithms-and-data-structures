#include <iostream>
#include <iomanip>
#include <vector>

#undef EXTENSIVE_OUTPUT

unsigned long comparisonsCounter = 0;
unsigned long swapsCounter = 0;


bool cmp1(int a, int b) {
    comparisonsCounter++;

    return a < b;
}


bool cmp2(int a, int b) {
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
        } while(cmp1(array[i], pivot));

        do {
            j--;
        } while(cmp2(array[j], pivot));

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

    quickSort(array, 0, n-1);

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