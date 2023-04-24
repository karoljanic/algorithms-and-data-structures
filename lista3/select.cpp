#include <iostream>
#include <random>
#include <chrono>
#include <iomanip>
#include <vector>
#include <algorithm>

#undef EXTENSIVE_OUTPUT

unsigned long comparisonsCounter = 0;
unsigned long swapsCounter = 0;

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

void assign(int&a, int& b) {
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

int select(std::vector<int>& array, size_t k, size_t m, size_t left, size_t right) {
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
    int median = select(medians, medians_number / 2, m, 0, medians_number - 1);

    size_t pivot_index = select_partition(array, left, right, median);

#ifdef EXTENSIVE_OUTPUT

    std::cout << "middle: ";
    for(const int& element : array) {
        std::cout << std::setw(2) << element << ' ';
    }
    std::cout << '\n';

#endif  // EXTENSIVE_OUTPUT

    if(pivot_index == k-1) {
        return array[pivot_index];
    }
    
    if(k-1 < pivot_index) {
        return select(array, k, m, left, pivot_index - 1);
    }

    return select(array, k, m, pivot_index + 1, right);
}

int main(int argc, char** argv) {
    if(argc != 3) {
        return 1;
    }

    size_t k = std::stoi(argv[1]);
    size_t m = std::stoi(argv[2]);

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

#ifdef EXTENSIVE_OUTPUT

    std::cout << "before: ";
    for(const int& element : array) {
        std::cout << std::setw(2) << element << ' ';
    }
    std::cout << '\n';
    
#endif  // EXTENSIVE_OUTPUT

    auto start = std::chrono::steady_clock::now();
    int result = select(array, k, m, 0, n-1);
    auto end = std::chrono::steady_clock::now();

    std::chrono::duration<double> elapsed_seconds = end-start;
    
#ifdef EXTENSIVE_OUTPUT

    std::cout << "after:  ";
    for(const int& element : array) {
        std::cout << std::setw(2) << element << ' ';
    }
    std::cout << '\n';

    std::sort(array.begin(), array.end(), std::less<int>());

    std::cout << "sorted: ";
    for(const int& element : array) {
        std::cout << std::setw(2) << element << ' ';
    }
    std::cout << '\n';

    std::cout << "\nk-th smallest element = " << result << '\n' <<
        "is correct: " << (array[k - 1] == result) << '\n' <<
        "cmps: " << comparisonsCounter << '\n' <<
        "swps: " << swapsCounter << '\n' <<
        "time: " << elapsed_seconds.count() * 1000 << '\n';
#else

    std::sort(array.begin(), array.end(), std::less<int>());
    std::cout << (array[k - 1] == result) << " " << comparisonsCounter << " " << swapsCounter << " " << elapsed_seconds.count() * 1000 << '\n';

#endif  // EXTENSIVE_OUTPUT 

}