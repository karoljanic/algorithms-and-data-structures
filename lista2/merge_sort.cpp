#include <iostream>
#include <iomanip>
#include <vector>

#define EXTENSIVE_OUTPUT

unsigned long comparisonsCounter = 0;
unsigned long swapsCounter = 0;


bool cmp(int a, int b) {
    comparisonsCounter++;

    return a <= b;
}


void swap(int& a, int& b) {
    swapsCounter++;

    int tmp = a;
    a = b;
    b = tmp;
}


void merge(std::vector<int>& array, size_t left, size_t mid, size_t right) {
    size_t leftArraySize = mid - left + 1;
    size_t rightArraySize = right - mid;

    std::vector<int> leftArray(array.begin() + left, array.begin() + mid + 1);
    std::vector<int> rightArray(array.begin() + mid + 1, array.begin() + right + 1);

    size_t leftArrayIndex = 0;
    size_t rightArrayIndex = 0;
    size_t mergeArrayIndex = left;

    while(leftArrayIndex < leftArraySize && rightArrayIndex < rightArraySize) {
        if(cmp(leftArray[leftArrayIndex], rightArray[rightArrayIndex])) {
            swap(array[mergeArrayIndex], leftArray[leftArrayIndex]);
            leftArrayIndex++;
        }
        else {
            swap(array[mergeArrayIndex], rightArray[rightArrayIndex]);
            rightArrayIndex++;
        }

        mergeArrayIndex++;
    }

    while(leftArrayIndex < leftArraySize) {
        swap(array[mergeArrayIndex], leftArray[leftArrayIndex]);
        leftArrayIndex++;
        mergeArrayIndex++;
    }

    while(rightArrayIndex < rightArraySize) {
        swap(array[mergeArrayIndex], rightArray[rightArrayIndex]);
        rightArrayIndex++;
        mergeArrayIndex++;
    }
}


void mergeSort(std::vector<int>& array, size_t begin, size_t end) {
    if(end <= begin) {
        return;
    }

    size_t mid = begin + (end - begin) / 2;
    mergeSort(array, begin, mid);
    mergeSort(array, mid + 1, end);

    merge(array, begin, mid, end);

#ifdef EXTENSIVE_OUTPUT

    for(const int& element : array) {
        std::cout << std::setw(2) << element << ' ';
    }
    std::cout << '\n';

#endif  // EXTENSIVE_OUTPUT

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

    mergeSort(array, 0, n - 1);

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
