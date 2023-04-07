#include <random>
#include <chrono>
#include <algorithm>
#include <iostream>


void generateRandomData(std::vector<int>& array, size_t n, int minVal, int maxVal) {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 gen(seed);

    std::uniform_int_distribution<unsigned int> dis(minVal, maxVal);

    for(int i = 0; i < n; i++) {
        array.push_back(dis(gen));
    }
}


void generateAscendingRandomData(std::vector<int>& array, size_t n, int minVal, int maxVal) {
    generateRandomData(array, n, minVal, maxVal);

    std::sort(array.begin(), array.end(), std::less<int>());
}


void generateDescendingRandomData(std::vector<int>& array, size_t n, int minVal, int maxVal) {
    generateRandomData(array, n, minVal, maxVal);

    std::sort(array.begin(), array.end(), std::greater<int>());
}


int main(int argc, char** argv) {
    if(argc != 3) {
        return 1;
    }

    char dataType = argv[1][0];

    int n;
    try {
        n = std::stoi(argv[2]);
    }
    catch(std::exception& e) {
        return 1;
    }

    if(n <= 0) {
        return 1;
    }

    int range = 2 * n - 1;
    
    std::vector<int> array;
    array.reserve(n);

    if(dataType == 'r') { // random data of size n from [0, range]
        generateRandomData(array, n, 0, range);
    }
    else if(dataType == 'a') { // random data of size n from [0, range] sorted ascending
        generateAscendingRandomData(array, n, 0, range);
    }
    else if(dataType == 'd') { // random data of size n from [0, range] sorted descending
        generateDescendingRandomData(array, n, 0, range);
    }
    else {
        return 1;
    }

    std::cout << n << '\n';
    for(const int& element : array) {
        std::cout << element << '\n';
    }
}
