#include <iostream>
#include <random>
#include <chrono>
#include <iomanip>
#include <vector>
#include <algorithm>

#undef EXTENSIVE_OUTPUT

unsigned long comparisonsCounter = 0;

bool equal(int a, int b) {
    comparisonsCounter++;

    return a == b;
}

bool greater(int a, int b) {
    comparisonsCounter++;

    return a > b;
}

bool binarySearch(std::vector<int>& array, int key, size_t left, size_t right) {
    if(left < right) {
        size_t mid = (left + right) / 2;
        
        if(equal(array[mid], key)) {
            return true;
        }

        if(greater(key, array[mid])) {
            return binarySearch(array, key, mid + 1, right);
        }

        return binarySearch(array, key, left, mid - 1);
    }
    
    if(equal(array[left], key)) {
        return true;
    }

    return false;
}

int main(int argc, char** argv) {
    if(argc != 2) {
        return 1;
    }

    size_t key = std::stoi(argv[1]);

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

    auto start = std::chrono::steady_clock::now();
    bool keyExist = binarySearch(array, key, 0, n-1);
    auto end = std::chrono::steady_clock::now();

    std::chrono::duration<double> elapsed_seconds = end-start;
    
#ifdef EXTENSIVE_OUTPUT

    std::cout << "array: ";
    for(const int& element : array) {
        std::cout << std::setw(2) << element << ' ';
    }
    std::cout << '\n';

    std::cout << "key " << key;
    if(keyExist) {
        std::cout << " exist\n";
    }
    else {
        std::cout << " not exist\n";
    }

    "time: " << elapsed_seconds.count() * 1000 << '\n';
    
#else

    std::cout << ((std::find(array.begin(), array.end(), key) != array.end()) == keyExist) << " " << comparisonsCounter << " " << elapsed_seconds.count() * 1000 << '\n';

#endif  // EXTENSIVE_OUTPUT 

}