#include <iostream>
#include <iomanip>
#include <vector>
#include <chrono>

#define EXTENSIVE_OUTPUT

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

bool smallerEqual(int a, int b) {
    comparisonsCounter++;

    return a <= b;
}

bool equal(int a, int b) {
    comparisonsCounter++;

    return a == b;
}

void swp(int& a, int& b) {
    swapsCounter++;

    int tmp = a;
    a = b;
    b = tmp;
}

void assign(int& a, int& b) {
    swapsCounter++;

    a = b;
}

void insertionSort(std::vector<int>& array, size_t left, size_t right) {
    for(int i=left+1;i<right+1;i++) {
        int key = array[i] ;
        size_t j = i;

        while(j > left && greater(array[j-1], key)) {
            assign(array[j], array[j-1]);
            j--;
        }
        array[j]= key;
    }
}


size_t select_partition(std::vector<int>& array, size_t left, size_t right, int pivot) {
    size_t pivot_index;
    for(pivot_index = left; pivot_index < right; pivot_index++) {
        if(equal(array[pivot_index], pivot)) {
            break;
        }
    }
    swp(array[right], array[pivot_index]);

    int i = left - 1;
    for (int j = left; j <= right - 1; j++) {
        if (smallerEqual(array[j], pivot)) {
            i++;
            swp(array[i], array[j]);
        }
    }
    swp(array[i + 1], array[right]);

    return i + 1;
}

int select(std::vector<int> array, size_t k, size_t m, size_t left, size_t right) {
    size_t n = right - left + 1;
        

    if(n + 1 <= m) {
        insertionSort(array, left, right);

        return array[k - 1];
    }

    std::vector<int> medians;
    for(size_t i = left; i <= right; i += m) {
        if(i + m < right) {
            insertionSort(array, i, i + m - 1);
            medians.push_back(array[i + 2]);
        }
        else {
            insertionSort(array, i, right);
            medians.push_back(array[(i + right) / 2]);
        }
    }

    size_t medians_number = medians.size();
    int median = select(medians, medians_number / 2 + 1, m, 0, medians_number - 1);

    size_t pivot_index = select_partition(array, left, right, median);

    if(pivot_index == k-1) {
        return array[pivot_index];
    }
    
    if(k-1 < pivot_index) {
        return select(array, k, m, left, pivot_index - 1);
    }

    return select(array, k, m, pivot_index + 1, right);
}


size_t quickSortPartition(std::vector<int>& array, size_t left, size_t right, int pivot) {
    size_t i = left - 1;
    size_t j = right + 1;

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

        swp(array[i], array[j]);
    }
}


void quickSort(std::vector<int>& array, size_t left, size_t right, int m) {
    if(right <= left) {
        return;
    }

    int median = select(array, (right - left + 1) / 2, 5, left, right);

    
    //size_t p = quickSortPartition(array, left, right, array[(left + right)/2]);
    size_t p = quickSortPartition(array, left, right, array[left]);

    //std::cout << "partition na " << left << ", " << right << " z pivotem " << median << "  p = " << p << std::endl;

    //std::cout << "median of: ";
    //for(const int& el: medians) { std::cout << el << " "; }
    //std::cout << " is " << median << std::endl;
    //std::cout << "left= " << left << "  right= " << right << "  p= " << p << "  median= " << median << std::endl;

#ifdef EXTENSIVE_OUTPUT

    for(const int& element : array) {
        std::cout << std::setw(2) << element << ' ';
    }
    std::cout << '\n';

#endif  // EXTENSIVE_OUTPUT

    quickSort(array, left, p, m);
    quickSort(array, p + 1, right, m);
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
    if(argc != 2) {
        return 1;
    }

    int m = std::atoi(argv[1]);

    size_t n;
    std::cin >> n;
    
    std::vector<int> array;
    array.reserve(n);
    int tmp;
    size_t n_copy = n;
    while(n_copy > 0) {
        std::cin >> tmp;
        array.push_back(tmp);
        n_copy--;
    }

    comparisonsCounter = 0;
    swapsCounter = 0;

    auto start = std::chrono::steady_clock::now();
    quickSort(array, 0, n-1, m);
    auto end = std::chrono::steady_clock::now();

    std::chrono::duration<double> elapsed_seconds = end-start;

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